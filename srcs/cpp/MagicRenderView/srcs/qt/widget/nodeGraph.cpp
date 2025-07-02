#include "nodeGraph.h"
#include <QMouseEvent>

#include <qt/menu/nodeAddMenu.h>
#include <QLabel>
#include <QPainter>

#include <qt/application/application.h>

#include "../mainWindow/mainWindow.h"

#include "../node/nodeLink/nodeLinkVector.h"

#include "../stack/varStack/IVarStack.h"

#include "qt/menu/action/nodeAddAction.h"
#include "qt/node/nodeComponent/INodeComponent.h"
#include "qt/stack/nodeStack/INodeStack.h"
#include "qt/stack/nodeStack/base/baseNodeStack.h"
#include "qt/tools/tools.h"

template< typename TUnity >
size_t randomId( std_vector_pairt< TUnity *, size_t > &storage_vector, TUnity *request_ui_ptr ) {
	auto count = storage_vector.size( );
	if( count == 0 ) {
		storage_vector.emplace_back( request_ui_ptr, 1 );
		return 1;
	}
	auto data = storage_vector.data( );
	size_t max = 0;
	max -= 1;

	for( size_t adId = 1; adId < max; ++adId ) {
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ].second == adId )
				break;
			else if( data[ index ].first == request_ui_ptr )
				return data[ index ].second;
		if( index == count ) {
			storage_vector.emplace_back( request_ui_ptr, adId );
			return adId;
		}
	}

	return 0;
}

template< typename TUnity >
size_t removeId( std_vector_pairt< TUnity *, size_t > &storage_vector, TUnity *request_ui_ptr ) {
	size_t result = 0;
	auto begin = storage_vector.begin( );
	auto end = storage_vector.end( );
	for( ; begin != end; ++begin )
		if( begin->first == request_ui_ptr ) {
			result = begin->second;
			storage_vector.emplace( begin );
			return result;
		}
	return result;
}

template< typename TUnity >
size_t getId( std_vector_pairt< TUnity *, size_t > &storage_vector, TUnity *request_ui_ptr ) {
	auto count = storage_vector.size( );
	if( count == 0 )
		return 0;
	auto data = storage_vector.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first == request_ui_ptr )
			return data[ index ].second;
	return 0;
}

template< typename TUnity >
inline static bool getUnitySecond( const std_vector_pairt< TUnity *, size_t > &storage_vector, const TUnity *request_ui_ptr, size_t *result_scond ) {
	*result_scond = 0;
	auto count = storage_vector.size( );
	if( count == 0 )
		return false;
	auto dataPtr = storage_vector.data( );
	for( size_t index = 0; index < count; ++index )
		if( dataPtr[ index ].first == request_ui_ptr ) {
			*result_scond = dataPtr[ index ].second;
			return true;
		}
	return false;
}

template< typename TUnity >
inline static TUnity * getUnityFirst( const std_vector_pairt< TUnity *, size_t > &storage_vector, const size_t &scond ) {
	auto count = storage_vector.size( );
	if( count == 0 )
		return nullptr;
	auto dataPtr = storage_vector.data( );
	for( size_t index = 0; index < count; ++index )
		if( dataPtr[ index ].second == scond )
			return dataPtr[ index ].first;
	return nullptr;
}

template< typename TUnity >
inline static bool hasUnity( const TUnity &unity, const std_vector< TUnity > &unity_vector ) {
	auto count = unity_vector.size( );
	if( count == 0 )
		return false;
	auto dataPtr = unity_vector.data( );
	for( size_t index = 0; index < count; ++index )
		if( dataPtr[ index ] == unity )
			return true;
	return false;
}

NodeGraph::NodeGraph( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	activeNodeWidget = nullptr;
	mainWindow = nullptr;
	nodeWidgetIDMutex = std_shared_ptr< std_mutex >( new std_mutex );
	nodeWidgetAdviseIDMutex = std_shared_ptr< std_mutex >( new std_mutex );

	nodeWidgetID = std_shared_ptr< std_vector_pairt< INodeWidget *, size_t > >( new std_vector_pairt< INodeWidget *, size_t > );
	nodeLinkItems = std_shared_ptr< NodeLinkVector >( new NodeLinkVector );
	nodeWidgetAdviseIDMutex->lock( );

	selectNodeWidget = nullptr;
	selectNodeComponent = nullptr;
	nodeMenu = new NodeAddMenu( this );
	auto nodeStack = INodeStack::getInstance< BaseNodeStack >( );
	auto nodeAddMenu = new NodeAddMenu( this );
	nodeAddMenu->setTitle( "标准节点" );
	nodeAddMenu->appendNodeStackObjectPtrToMenuSubMenu( nodeStack );
	nodeMenu->addMenu( nodeAddMenu );
	setMouseTracking( true );
	mouseEventStatus = MouseEventType::Init;

	connect( nodeMenu, &NodeAddMenu::activeAction, [this] ( QAction *action ) ->void {
		auto instance = INodeStack::getInstance< BaseNodeStack >( );
		QString functionName;
		auto nodeAddAction = qobject_cast< NodeAddAction * >( action );
		if( nodeAddAction )
			functionName = nodeAddAction->getFunctionName( );
		else
			functionName = action->text( );
		auto generateNode = instance->generateNode( functionName ); // 节点生成
		if( generateNode ) {
			generateNode->hide( );
			nodeWidgets.emplace_back( generateNode );
			generateNode->move( currentMouseInWidgetPos );
			generateNode->setParent( this );
			generateNode->connectNodeGraphWidget( this );
			generateNode->show( );
			updateMinSize( );
			emit generateNodeWidget( this, generateNode, nodeWidgets );
		} else
			tools::debug::printError( functionName );
	} );
	mousePosLabel = new QLabel( this );
	QImage image( ":/images/add_node.png" );
	mousePosLabel->setPixmap( QPixmap::fromImage( image ) );
	mousePosLabel->show( );
	mousePosLabelHalfSize = image.size( ) / 2;
	Application::setNewNodeGraph( this );
}
NodeGraph::~NodeGraph( ) {
}
bool NodeGraph::findPosNodeInfo( const QPoint &check_pos, INodeWidget **result_node_widget, INodeComponent **result_node_component ) {
	size_t count = nodeWidgets.size( );
	if( count == 0 )
		return false;
	auto nodeWidgetVectDataPtr = nodeWidgets.data( );
	INodeWidget *nodeWidgetPtr;
	QRect geometry;
	for( size_t index = 0; index < count; ++index ) {
		nodeWidgetPtr = nodeWidgetVectDataPtr[ index ];
		geometry = nodeWidgetPtr->geometry( );
		if( geometry.contains( check_pos ) == false )
			continue;
		*result_node_widget = nodeWidgetPtr;
		auto checkPos = check_pos - nodeWidgetPtr->pos( );
		*result_node_component = nodeWidgetPtr->getPosNodeComponent( checkPos );
		return true;
	}
	return false;
}

void NodeGraph::updateMinSize( ) {
	QRect newRect = this->contentsRect( );
	for( auto nodeWidgetPtr : nodeWidgets )
		newRect = newRect.united( nodeWidgetPtr->geometry( ) );
	QSize newSize = newRect.size( );
	setMinimumSize( newSize );
}
void NodeGraph::mouseReleaseEvent( QMouseEvent *event ) {
	cursorPos = QCursor::pos( );
	currentMouseInWidgetPos = event->pos( );
	INodeComponent *inputNodeComponent = nullptr, *outputNodeComponent = nullptr;
	INodeWidget *inputNodeWidget = nullptr, *outputNodeWidget = nullptr;
	switch( mouseEventStatus ) {
		// 在按下之后抬起事件
		case MouseEventType::Press : {
			if( selectNodeComponent == nullptr && selectNodeWidget == nullptr ) {
				// 鼠标按键
				Qt::MouseButton mouseButton = event->button( );

				switch( mouseButton ) {
					case Qt::RightButton : // 使用配置的位置显示菜单
						nodeMenu->move( cursorPos );
						nodeMenu->show( );
						break;
					case Qt::LeftButton : // 配置位置
						QPoint point( currentMouseInWidgetPos.x( ) - mousePosLabelHalfSize.width( ), currentMouseInWidgetPos.y( ) - mousePosLabelHalfSize.height( ) );
						mousePosLabel->move( point );
						mousePosLabel->raise( );
						break;
				}
			}
		}
		case MouseEventType::Move :
			if( selectNodeComponent ) {
				NodeLinkItem nodeLinkItem;
				INodeComponent::Channel_Type componentChannel = selectNodeComponent->getComponentChannel( );
				switch( componentChannel ) {
					case INodeComponent::Channel_Type::Normal_Default :
						break;
					case INodeComponent::Channel_Type::Input_Read :
						// 允许配置输入
						if( nodeLinkItem.setInput( selectNodeWidget, selectNodeComponent ) == false )
							break;
						// 查找输出目标
						if( findPosNodeInfo( currentMouseInWidgetPos, &outputNodeWidget, &outputNodeComponent ) == false )
							break;
						// 输出组件是否存在
						if( !outputNodeComponent )
							break;
						// 获取输出组件的作为位置
						if( outputNodeComponent->getComponentLinkPos( outputNodeComponent, selectNodeComponentPoint ) == false )
							break;
						// 配置输出位置
						if( nodeLinkItem.setOutput( outputNodeWidget, outputNodeComponent ) == false )
							break;
						// 是否已经存在重复链接
						if( nodeLinkItems->hasItem( nodeLinkItem ) == true )
							break;
						// 输入组件是否允许重复输入
						if( selectNodeComponent->isOverlayMulVar( ) == false )
							if( nodeLinkItems->linkHasInputUnity( selectNodeComponent ) && nodeLinkItems->linkRemoveFirstInputItem( selectNodeComponent ) != 1 )
								tools::debug::printError( "无法断开链接 : " + selectNodeWidget->getNodeTitle( ) + "->" + selectNodeComponent->getNodeComponentName( ) );
						// 加入链接
						nodeLinkItems->emplace_back( nodeLinkItem );
						break;
					case INodeComponent::Channel_Type::Output_Write :
						// 配置输出组件
						if( nodeLinkItem.setOutput( selectNodeWidget, selectNodeComponent ) == false )
							break;
						// 查找输入组件
						if( findPosNodeInfo( currentMouseInWidgetPos, &inputNodeWidget, &inputNodeComponent ) == false )
							break;
						// 不存在输入组件
						if( !inputNodeComponent )
							break;
						// 获取输入组件位置
						if( inputNodeWidget->getComponentLinkPos( inputNodeComponent, selectNodeComponentPoint ) == false )
							break;
						// 配置输入组件
						if( nodeLinkItem.setInput( inputNodeWidget, inputNodeComponent ) == false )
							break;
						// 是否已经存在重复链接
						if( nodeLinkItems->hasItem( nodeLinkItem ) == true )
							break;
						// 是否允许重复输入
						if( inputNodeComponent->isOverlayMulVar( ) == false )
							if( nodeLinkItems->linkHasInputUnity( inputNodeComponent ) && nodeLinkItems->linkRemoveFirstInputItem( inputNodeComponent ) != 1 )
								tools::debug::printError( "无法断开链接 : " + inputNodeWidget->getNodeTitle( ) + "->" + inputNodeComponent->getNodeComponentName( ) );
						// 配置链接
						nodeLinkItems->emplace_back( nodeLinkItem );
						break;
				}
			} else if( selectNodeWidget )
				updateMinSize( );
			break;
	}
	mouseEventStatus = MouseEventType::Release;
	selectNodeWidget = nullptr;
	selectNodeComponent = nullptr;
	repaint( );
}
void NodeGraph::mouseMoveEvent( QMouseEvent *event ) {
	cursorPos = QCursor::pos( );
	currentMouseInWidgetPos = event->pos( );
	if( selectNodeComponent );
	else if( selectNodeWidget && geometry( ).contains( currentMouseInWidgetPos ) ) {
		QPoint point = currentMouseInWidgetPos - selectNodeWidgetOffset;
		point.setX( std::max( 0, point.x( ) ) );
		point.setY( std::max( 0, point.y( ) ) );
		selectNodeWidget->move( point );
	}
	mouseEventStatus = MouseEventType::Move;
	repaint( );
}

bool NodeGraph::overSerializeToObjectData( const std_vector_pairt< INodeWidget *, size_t > &over_widget_list, const std_vector< NodeLinkItem > &new_link_items_vector ) {
	nodeWidgetIDMutex->lock( );
	nodeWidgets.clear( );
	auto data = nodeWidgetID->data( );
	size_t count = nodeWidgetID->size( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete data[ index ].first;
	nodeWidgetID->clear( );
	nodeLinkItems->clear( );

	size_t overCount = over_widget_list.size( );
	auto ptrData = over_widget_list.data( );
	index = 0;
	for( ; index < overCount; ++index ) {
		auto pair = ptrData[ index ];
		nodeWidgetID->emplace_back( pair );
		INodeWidget *nodeWidget = pair.first;
		nodeWidgets.emplace_back( nodeWidget );
		nodeWidget->setParent( this );
	}
	for( auto item : new_link_items_vector )
		nodeLinkItems->emplace_back( item );
	nodeWidgetIDMutex->unlock( );
	for( auto node : nodeWidgets )
		node->show( );

	updateMinSize( );
	repaint( );
	return true;
}
bool NodeGraph::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	nodeWidgetIDMutex->lock( );
	/// 累加数据
	std_vector< uint8_t > mulStdData;
	size_t count;
	QList< INodeWidget * > nodeWidgets = findChildren< INodeWidget * >( );
	// 排序表达式
	auto lambda = [] ( std_pairt< INodeComponent *, size_t > &left, std_pairt< INodeComponent *, size_t > &right ) {
		return left.second < right.second;
	};
	uint8_t *lastPtr;
	uint8_t *data;;
	size_t index;
	int64_t pos;
	qsizetype nodeWidgetCount = nodeWidgets.size( );
	qsizetype nodeWidgetIndex = 0;
	INodeWidget **nodeWidgetDataPtr = nodeWidgets.data( );
	size_t activeNodeCount = 0;
	// 节点列表
	for( ; nodeWidgetIndex < nodeWidgetCount; ++nodeWidgetIndex ) {
		size_t activeComponentCount = 0;
		INodeWidget *nodeWidget = nodeWidgetDataPtr[ nodeWidgetIndex ];
		size_t nodeWidgetId;
		::getUnitySecond( *nodeWidgetID, nodeWidget, &nodeWidgetId );
		if( nodeWidgetId == 0 )
			continue; // 无效，则跳过这次
		++activeNodeCount;

		std_vector_pairt< INodeComponent *, size_t > componentId = nodeWidget->getComponentID( );
		std::ranges::sort( componentId, lambda );
		auto pairDataPtr = componentId.data( );
		auto componentIDCount = componentId.size( );

		std_vector< uint8_t > nodeCompoent;
		for( index = 0; index < componentIDCount; ++index )
			if( pairDataPtr[ index ].second == 0 )
				continue;
			else if( pairDataPtr[ index ].first->getVarObject( ) != nullptr ) {
				std_vector< uint8_t > componentResult;

				if( pairDataPtr[ index ].first->getVarObject( )->serializeToVectorData( &componentResult ) == false ) {
					tools::debug::printError( "序列化失败 : " + nodeWidget->getNodeTitle( ) + " -> " + pairDataPtr[ index ].first->getNodeComponentName( ) );
					nodeWidgetIDMutex->unlock( );
					return false;
				}

				++activeComponentCount;
				std_vector< uchar > idData;
				toData( pairDataPtr[ index ].second, &idData );
				nodeCompoent.append_range( idData );
				nodeCompoent.append_range( componentResult );
			}
		count = nodeCompoent.size( );
		// 节点 id 占用
		size_t nodeWidgetIDSize = sizeof( nodeWidgetId );
		// 有效组件占用
		size_t activeComponentCountSize = sizeof( activeComponentCount );
		// 单个坐标有效占用
		size_t posSize = sizeof pos;
		// 数据计数占用
		size_t componentDataCountSize = sizeof( count );
		// 追加数量 = 组件大小 + ( 组件数据量+ ID 占用 +  xy坐标)
		index = nodeWidgetIDSize + activeComponentCountSize + count + posSize + posSize + componentDataCountSize;
		std_vector< uint8_t > result;
		lastPtr = converQMetaObjectInfoToUInt8Vector( &result, nodeWidget->metaObject( ), nodeWidget->getNodeStack( )->getStackTypeNames( ), nodeWidget->getNodeNames( ), index );
		// 赋值节点ID
		*( decltype(nodeWidgetId) * ) lastPtr = nodeWidgetId; // 1 * sizeof( size_t ) 
		lastPtr += nodeWidgetIDSize;
		// 赋值 x
		pos = nodeWidget->x( );
		*( decltype(pos) * ) lastPtr = pos;  // 2 * sizeof( size_t ) 
		lastPtr += posSize;
		// 赋值 y
		pos = nodeWidget->y( );
		*( decltype(pos) * ) lastPtr = pos;  // 3 * sizeof( size_t ) 
		lastPtr += posSize;

		// 赋值组件数据量
		*( decltype(activeComponentCount) * ) lastPtr = activeComponentCount;  // 4 * sizeof( size_t ) 
		lastPtr += activeComponentCountSize;

		// 赋值组件占用
		*( decltype(count) * ) lastPtr = count;  // 5 * sizeof( size_t ) 
		lastPtr += componentDataCountSize;
		// 拷贝组件数据
		data = nodeCompoent.data( );
		auto mul = result.size( ) - ( lastPtr - result.data( ) );
		if( mul < count ) {
			tools::debug::printError( "存储数量不足填充后续数据，请检查大小是否异常。( " + QString::number( mul ) + " < " + QString::number( count ) + " ) 判定成立" );
			nodeWidgetIDMutex->unlock( );
			return false;
		}
		for( index = 0; index < count; ++index )
			lastPtr[ index ] = data[ index ];
		mulStdData.append_range( result );
	}
	// 连接列表
	auto linkItemsVector = nodeLinkItems->toVector( );
	auto linkItem = linkItemsVector.data( );
	size_t linkCount = linkItemsVector.size( );
	std_vector< uchar > linkBuff;
	for( index = 0; index < linkCount; ++index ) {
		size_t nodeWidgetId;
		std_vector< uchar > idBuff;
		auto inputNodeComponentInfo = linkItem[ index ].getInputNodeComponentInfo( );
		::getUnitySecond( *nodeWidgetID, inputNodeComponentInfo.first, &nodeWidgetId );
		toData( nodeWidgetId, &idBuff );
		linkBuff.append_range( idBuff );
		nodeWidgetId = inputNodeComponentInfo.second->getNodeWidgetAtNodeCompoentID( );
		toData( nodeWidgetId, &idBuff );
		linkBuff.append_range( idBuff );

		inputNodeComponentInfo = linkItem[ index ].getOutputNodeComponentInfo( );
		::getUnitySecond( *nodeWidgetID, inputNodeComponentInfo.first, &nodeWidgetId );
		toData( nodeWidgetId, &idBuff );
		linkBuff.append_range( idBuff );
		nodeWidgetId = inputNodeComponentInfo.second->getNodeWidgetAtNodeCompoentID( );
		toData( nodeWidgetId, &idBuff );
		linkBuff.append_range( idBuff );
	}
	size_t mulCount = mulStdData.size( );
	size_t linkBuffCount = linkBuff.size( );
	count = mulCount + linkBuffCount;
	// 大小端 + 节点数
	index = 1 + sizeof size_t + sizeof qsizetype + sizeof( linkCount ) + sizeof( linkBuffCount );
	result_data_vector->resize( count + index );

	lastPtr = result_data_vector->data( );
	*lastPtr = isBegEndian( );
	lastPtr += 1;
	*( decltype(activeNodeCount) * ) lastPtr = activeNodeCount;
	lastPtr += sizeof activeNodeCount;
	*( decltype(mulCount) * ) lastPtr = mulCount;
	lastPtr += sizeof mulCount;
	// 拷贝数据
	data = mulStdData.data( );
	for( index = 0; index < mulCount; ++index )
		lastPtr[ index ] = data[ index ];
	lastPtr += index;
	*( decltype(linkCount) * ) lastPtr = linkCount;
	lastPtr += sizeof linkCount;
	*( decltype(linkBuffCount) * ) lastPtr = linkBuffCount;
	lastPtr += sizeof linkBuffCount;
	data = linkBuff.data( );
	for( index = 0; index < linkBuffCount; ++index )
		lastPtr[ index ] = data[ index ];
	count = result_data_vector->size( );
	nodeWidgetIDMutex->unlock( );
	return count;
}
size_t NodeGraph::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	nodeWidgetIDMutex->lock( );

	auto cood = *read_data_vector != isBegEndian( );
	size_t nodeWidgetCount = *( size_t * ) ( read_data_vector + 1 );
	if( cood )
		ISerialize::converEndian( nodeWidgetCount );
	// 数据头
	size_t jumpCompCount = sizeof size_t + 1;
	if( nodeWidgetCount == 0 ) {
		nodeWidgetIDMutex->unlock( );
		return sizeof jumpCompCount;
	}
	// 获取节点个数
	auto lastPtr = read_data_vector + jumpCompCount;
	size_t needCount = *( size_t * ) ( lastPtr );
	if( cood )
		ISerialize::converEndian( needCount );
	if( needCount > data_count ) {
		tools::debug::printError( "参考数据不满足所需数据" );
		nodeWidgetIDMutex->unlock( );
		return 0;
	}
	lastPtr += sizeof size_t;

	size_t index;
	size_t useCount;
	size_t inheritCount;
	size_t id;
	uchar beg;
	int64_t x;
	int64_t y;
	qsizetype idIndex;
	size_t componentCount;
	std_vector< QString > stackNames;
	std_vector< QString > meteObjectNames;
	std_vector< QString > typeNames;
	INodeStack *nodeStack;
	INodeWidget *generateNode;
	std_vector< QString > inheritInfo;
	std_vector_pairt< INodeComponent *, size_t > componentId;
	std_vector_pairt< INodeComponent *, size_t > buffComponentId;
	size_t componentIdCount;
	std::pair< INodeComponent *, size_t > *componentDataPtr;
	std_shared_ptr< ITypeObject > varObject;
	std_shared_ptr< IVarStack > varStack;
	std_vector_pairt< INodeWidget *, size_t > overNodeWidget;
	auto surplus = data_count - jumpCompCount;
	for( size_t serIndex = 0; serIndex < nodeWidgetCount; ++serIndex ) {
		useCount = ISerialize::SerializeInfo::getSerializeInfo( lastPtr, surplus, &beg, &stackNames, &meteObjectNames, &typeNames );
		if( useCount == 0 ) {
			tools::debug::printError( "无法从序列化中获取对象信息" );
			nodeWidgetIDMutex->unlock( );
			return 0;
		}
		nodeStack = INodeStack::getInstance( stackNames[ 0 ] );
		if( nodeStack == nullptr ) {
			tools::debug::printError( "无法匹配适应的节点生成器 : " + stackNames[ 0 ] );
			nodeWidgetIDMutex->unlock( );
			return 0;
		}
		generateNode = nodeStack->generateNode( typeNames[ 0 ] );
		if( generateNode == nullptr ) {
			tools::debug::printError( "无法生成对应的节点 : " + typeNames[ 0 ] );
			nodeWidgetIDMutex->unlock( );
			return 0;
		}
		inheritInfo = ISerialize::SerializeInfo::getMetaInheritInfo( generateNode->metaObject( ) );
		inheritCount = inheritInfo.size( );
		if( inheritCount != meteObjectNames.size( ) ) {
			tools::debug::printError( "节点继承关系不匹配 : " + typeNames[ 0 ] );
			nodeWidgetIDMutex->unlock( );
			return 0;
		}
		for( index = 0; index < inheritCount; ++index )
			if( meteObjectNames[ index ] != inheritInfo[ index ] ) {
				tools::debug::printError( "节点继承关系不匹配 : " + typeNames[ 0 ] );
				nodeWidgetIDMutex->unlock( );
				return 0;
			}
		// 获取 id
		lastPtr = lastPtr + useCount;
		id = *( ( size_t * ) lastPtr );

		auto pair = overNodeWidget.data( );
		size_t pairCount = overNodeWidget.size( );
		for( size_t pariIndex = 0; pariIndex < pairCount; ++pariIndex )
			if( pair[ pariIndex ].second == id ) {
				tools::debug::printError( "数据存在重复 ID : " + generateNode->getNodeTitle( ) + " => " + pair[ pariIndex ].first->getNodeTitle( ) );
				nodeWidgetIDMutex->unlock( );
				return 0;
			}
		overNodeWidget.emplace_back( generateNode, id );
		lastPtr += sizeof( id );
		// 获取 x
		x = *( ( int64_t * ) lastPtr );
		lastPtr += sizeof x;
		// 获取 y
		y = *( ( int64_t * ) lastPtr );
		generateNode->move( x, y );
		lastPtr += sizeof y;
		// 获取组件数目
		componentCount = *( ( decltype(componentCount) * ) lastPtr );
		lastPtr += sizeof componentCount;
		surplus = data_count - ( lastPtr - read_data_vector );
		if( componentCount == 0 )
			continue; // 组件为 0
		id = *( ( decltype(id) * ) lastPtr );
		lastPtr += sizeof id;
		if( surplus < useCount ) {
			tools::debug::printError( "数据量使用异常" );
			nodeWidgetIDMutex->unlock( );
			return 0;
		}
		surplus = data_count - ( lastPtr - read_data_vector );
		if( id > surplus ) {
			tools::debug::printError( "数据量无法配置节点组件信息" );
			nodeWidgetIDMutex->unlock( );
			return 0;
		}
		if( id == 0 )
			continue;
		componentId = generateNode->getComponentID( );
		componentIdCount = componentId.size( );
		componentDataPtr = componentId.data( );
		buffComponentId.clear( );
		for( idIndex = 0; idIndex < componentIdCount; ++idIndex )
			if( componentDataPtr[ idIndex ].second == 0 || componentDataPtr[ idIndex ].first->getVarObject( ) == nullptr )
				continue;
			else
				buffComponentId.emplace_back( componentDataPtr[ idIndex ] );

		componentIdCount = buffComponentId.size( );
		if( componentIdCount != componentCount ) {
			tools::debug::printError( "节点组件不匹配，请检查节点 : " + generateNode->getNodeNames( )[ 0 ] + " 是否异常 ( " + QString::number( componentIdCount ) + " != " + QString::number( componentCount ) + " ) " );
			nodeWidgetIDMutex->unlock( );
			return 0;
		}

		componentDataPtr = buffComponentId.data( );
		for( idIndex = 0; idIndex < componentIdCount; ++idIndex ) {
			id = *( ( decltype(id) * ) lastPtr );
			if( id == 0 ) {
				tools::debug::printError( "组件id序列为 : 0 。出现异常，请检查节点 : " + generateNode->getNodeNames( )[ 0 ] + " 是否异常" );
				nodeWidgetIDMutex->unlock( );
				return 0;
			}
			lastPtr += sizeof id;
			surplus = data_count - ( lastPtr - read_data_vector );
			for( index = 0; index < componentIdCount; ++index )
				if( componentDataPtr[ index ].second == id ) {
					varObject = componentDataPtr[ index ].first->getVarObject( );
					if( varObject != nullptr ) {
						useCount = ISerialize::SerializeInfo::getSerializeInfo( lastPtr, surplus, &beg, &stackNames, &meteObjectNames, &typeNames );
						if( useCount == 0 ) {
							tools::debug::printError( "组件id序列为 : " + QString::number( id ) + " 出现异常，请检查节点 : " + generateNode->getNodeNames( )[ 0 ] + " 是否异常" );
							nodeWidgetIDMutex->unlock( );
							return 0;
						}
						varStack = IVarStack::getInstance( stackNames[ 0 ] );
						if( varStack == nullptr ) {
							tools::debug::printError( "无法找到匹配变量堆栈 : " + stackNames[ 0 ] );
							nodeWidgetIDMutex->unlock( );
							return 0;
						}
						varObject = varStack->generateVar( typeNames[ 0 ] );
						if( varObject == nullptr ) {
							tools::debug::printError( "变量堆栈创建类型失败 : " + stackNames[ 0 ] + " ! " + typeNames[ 0 ] );
							nodeWidgetIDMutex->unlock( );
							return 0;
						}
						useCount = varObject->serializeToObjectData( lastPtr, surplus );
						if( useCount == 0 ) {
							tools::debug::printError( "变量反序列化失败 : " + stackNames[ 0 ] + " ! " + typeNames[ 0 ] );
							nodeWidgetIDMutex->unlock( );
							return 0;
						}
						lastPtr += useCount;
						componentDataPtr[ index ].first->setVar( varObject );
					}
					index = 0;
					break;
				}
			if( index != 0 ) {
				tools::debug::printError( "组件id序列为 : " + QString::number( id ) + " 出现异常，请检查节点 : " + generateNode->getNodeNames( )[ 0 ] + " 是否异常" );
				nodeWidgetIDMutex->unlock( );
				return 0;
			}
			size_t mod = lastPtr - read_data_vector;
			if( data_count < mod ) {
				tools::debug::printError( "数据量使用异常" );
				nodeWidgetIDMutex->unlock( );
				return 0;
			}
		}
	}
	size_t linkCount = *( size_t * ) lastPtr;
	lastPtr += sizeof size_t;
	size_t linkDataCount = *( size_t * ) lastPtr;
	lastPtr += sizeof size_t;
	std_vector< NodeLinkItem > newLinkItemsVector;
	if( linkCount != 0 && linkDataCount != 0 ) {
		surplus = data_count - ( lastPtr - read_data_vector );
		if( linkDataCount > surplus ) {
			tools::debug::printError( "数据量使用异常，剩余数据不足填充链表" );
			nodeWidgetIDMutex->unlock( );
			return 0;
		}
		for( index = 0; index < linkCount; ++index ) {
			NodeLinkItem linkItem;
			size_t inputWidgetID = *( size_t * ) lastPtr;
			lastPtr += sizeof size_t;

			auto inputLink = getUnityFirst( overNodeWidget, inputWidgetID );
			size_t inputComponentID = *( size_t * ) lastPtr;
			lastPtr += sizeof size_t;
			auto componetFromId = inputLink->getComponetFromID( inputComponentID );
			linkItem.setInput( inputLink, componetFromId );

			size_t outputWidgetID = *( size_t * ) lastPtr;
			lastPtr += sizeof size_t;
			inputLink = getUnityFirst( overNodeWidget, outputWidgetID );
			size_t outputComponentID = *( size_t * ) lastPtr;
			lastPtr += sizeof size_t;
			componetFromId = inputLink->getComponetFromID( outputComponentID );
			linkItem.setOutput( inputLink, componetFromId );
			newLinkItemsVector.emplace_back( linkItem );
		}
	} else if( linkDataCount == 0 && linkCount == 0 );
	else if( linkDataCount == 0 || linkCount == 0 ) {
		tools::debug::printError( "链接列表数据异常" );
		nodeWidgetIDMutex->unlock( );
		return 0;
	}

	useCount = lastPtr - read_data_vector;
	nodeWidgetIDMutex->unlock( );
	overSerializeToObjectData( overNodeWidget, newLinkItemsVector );
	return useCount;
}
size_t NodeGraph::getNodeWidgetID( const INodeWidget *node_widget ) const {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	size_t resultID = 0;
	if( ::getUnitySecond( *nodeWidgetID, node_widget, &resultID ) )
		return resultID;
	return 0;
}
INodeWidget * NodeGraph::getNodeWidgetFromID( const size_t &id ) const {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	return getUnityFirst( *nodeWidgetID, id );
}
void NodeGraph::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	selectNodeWidget = nullptr;
	selectNodeComponent = nullptr;
	mouseEventStatus = MouseEventType::Press;
	cursorPos = QCursor::pos( );
	currentMouseInWidgetPos = event->pos( );
	QRect geometry;
	for( auto nodeWidget : nodeWidgets ) {
		geometry = nodeWidget->geometry( );
		if( geometry.contains( currentMouseInWidgetPos ) == false )
			continue;
		selectNodeWidget = nodeWidget;
		selectNodeWidgetOffset = currentMouseInWidgetPos - nodeWidget->pos( );
		selectNodeComponent = nodeWidget->getPosNodeComponent( selectNodeWidgetOffset );
		if( selectNodeWidget->getComponentLinkPos( selectNodeComponent, selectNodeComponentPoint ) == false /* 没有找到可链接的组件 */ )
			selectNodeComponent = nullptr;
		auto old = activeNodeWidget;
		activeNodeWidget = selectNodeWidget;
		emit selectActiveNodeWidget( this, activeNodeWidget, old );
		repaint( );
		return;
	}
}
void NodeGraph::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	QPoint start, end;

	for( auto item : nodeLinkItems->toVector( ) )
		if( item.getInputOutputPos( &start, &end ) )
			painter.drawLine( start, end );
	if( selectNodeComponent /* 绘制即时连线 */ ) {
		painter.drawLine( selectNodeComponentPoint, currentMouseInWidgetPos );
	}
}

size_t NodeGraph::registerID( INodeWidget *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	return ::randomId( *nodeWidgetID, request_ui_ptr );
}
size_t NodeGraph::registerID( INodeWidget *request_ui_ptr, size_t advise_id ) {
	size_t count = nodeWidgetID->size( );
	if( count == 0 ) {
		nodeWidgetID->emplace_back( request_ui_ptr, advise_id );
		return advise_id;
	}
	auto data = nodeWidgetID->data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].second == advise_id )
			return 0;
	nodeWidgetID->emplace_back( request_ui_ptr, advise_id );
	return advise_id;
}
size_t NodeGraph::removeId( INodeWidget *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	return ::removeId( *nodeWidgetID, request_ui_ptr );
}
void NodeGraph::error( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &msg, size_t error_code, size_t error_line ) {
	std_vector< std_pairt< QString, size_t > > pair;
	qDebug( ) << tools::debug::getFunctionName( 1, pair )[ 0 ].first << " ( " << pair[ 0 ].second << " )  : " << send_obj_ptr->objectName( ) << " :->: " << "error( " << error_code << " ) " << error_line;
}
void NodeGraph::finish( INodeWidget *send_obj_ptr, const std_shared_ptr< ITypeObject > &result_type_object, size_t return_code, size_t over_line ) {
	std_vector< std_pairt< QString, size_t > > pair;
	qDebug( ) << tools::debug::getFunctionName( 1, pair )[ 0 ].first << " ( " << pair[ 0 ].second << " )  : " << send_obj_ptr->objectName( ) << " :->: " << over_line;
}
void NodeGraph::requestNodeWidgetID( INodeWidget *request_node_widget_ptr ) {
	size_t id = registerID( request_node_widget_ptr );
	request_node_widget_ptr->registerIDFinish( id );
}
void NodeGraph::requestNodeWidgetAdviseID( INodeWidget *request_node_widget_ptr, size_t advise_id ) {
	if( nodeWidgetAdviseIDMutex.get( )->try_lock( ) ) {
		advise_id = registerID( request_node_widget_ptr, advise_id );
		nodeWidgetAdviseIDMutex->unlock( );
		request_node_widget_ptr->registerIDFinish( advise_id );
	} else
		request_node_widget_ptr->registerIDFinish( getId( *nodeWidgetID, request_node_widget_ptr ) );
}
void NodeGraph::destoryNodeWidgetID( INodeWidget *request_node_widget_ptr ) {
	removeId( request_node_widget_ptr );
}
