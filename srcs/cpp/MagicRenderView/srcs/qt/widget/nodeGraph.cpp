#include "nodeGraph.h"
#include <QMouseEvent>

#include <qt/menu/nodeAddMenu.h>
#include <QLabel>
#include <QPainter>

#include <qt/application/application.h>

#include "../stack/varStack/IVarStack.h"

#include "qt/functionDeclaration/IFunctionDeclaration.h"
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
	while( max < count )
		if( data[ max ].first == request_ui_ptr )
			return data[ max ].second;
		else
			++max;
	max = 1;
	while( max != 0 )
		if( data[ max ].second == max )
			++max;
		else {
			storage_vector.emplace_back( request_ui_ptr, max );
			return max;
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
	nodeComponentIDMutex = std_shared_ptr< std_mutex >( new std_mutex );
	nodeWidgetIDMutex = std_shared_ptr< std_mutex >( new std_mutex );
	nodeWidgetAdviseIDMutex = std_shared_ptr< std_mutex >( new std_mutex );
	nodeComponentAdviseIDMutex = std_shared_ptr< std_mutex >( new std_mutex );

	nodeWidgetAdviseIDMutex->lock( );
	nodeComponentAdviseIDMutex->lock( );

	selectNodeWidget = nullptr;
	selectNodeComponent = nullptr;
	nodeMenu = new NodeAddMenu( this );
	nodeMenu->init< BaseNodeStack >( );
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
		} else
			tools::debug::printError( functionName );
	} );
	mousePosLabel = new QLabel( this );
	mousePosLabel->setPixmap( QPixmap::fromImage( QImage( ":/images/add_node.png" ) ) );
	mousePosLabel->hide( );
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
	QRect newRect = this->rect( );
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
						if( mousePosLabel->isHidden( ) ) {
							mousePosLabel->show( );
							mousePosLabel->move( currentMouseInWidgetPos );
						} else if( mousePosLabel->geometry( ).contains( currentMouseInWidgetPos ) ) {
							nodeMenu->move( cursorPos );
							nodeMenu->show( );
						} else
							mousePosLabel->move( currentMouseInWidgetPos );
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
						if( hasUnity( nodeLinkItem, nodeLinkItems ) == true )
							break;
						// 输入组件是否允许重复输入
						if( selectNodeComponent->isOverlayMulVar( ) == false )
							if( linkHasInputUnity( selectNodeComponent ) && linkRemoveFirstInputItem( selectNodeComponent ) != 1 )
								tools::debug::printError( "无法断开链接 : " + selectNodeWidget->getNodeTitle( ) + "->" + selectNodeComponent->getNodeComponentName( ) );
						// 加入链接
						nodeLinkItems.emplace_back( nodeLinkItem );
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
						if( hasUnity( nodeLinkItem, nodeLinkItems ) == true )
							break;
						// 是否允许重复输入
						if( inputNodeComponent->isOverlayMulVar( ) == false )
							if( linkHasInputUnity( inputNodeComponent ) && linkRemoveFirstInputItem( inputNodeComponent ) != 1 )
								tools::debug::printError( "无法断开链接 : " + inputNodeWidget->getNodeTitle( ) + "->" + inputNodeComponent->getNodeComponentName( ) );
						// 配置链接
						nodeLinkItems.emplace_back( nodeLinkItem );
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
	mouseEventStatus = MouseEventType::Move;
	cursorPos = QCursor::pos( );
	currentMouseInWidgetPos = event->pos( );
	if( selectNodeComponent ) {
	} else if( selectNodeWidget && geometry( ).contains( currentMouseInWidgetPos ) ) {
		QPoint point = currentMouseInWidgetPos - selectNodeWidgetOffset;
		point.setX( std::max( 0, point.x( ) ) );
		point.setY( std::max( 0, point.y( ) ) );
		selectNodeWidget->move( point );
	}
	repaint( );
}

int NodeGraph::linkHasUnity( const INodeComponent *unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return 0;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	int has;
	for( size_t index = 0; index < count; ++index )
		if( ( has = nodeLinkItemDataPtr[ index ].has( unity ), has != 0 ) )
			return has;
	return 0;
}

int NodeGraph::linkHasUnity( const INodeWidget *unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return 0;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	int has;
	for( size_t index = 0; index < count; ++index )
		if( ( has = nodeLinkItemDataPtr[ index ].has( unity ), has != 0 ) )
			return has;
	return 0;
}
int NodeGraph::linkHasInputUnity( const INodeComponent *input_unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeLinkItemDataPtr[ index ].hasInput( input_unity ) )
			return true;
	return false;
}
int NodeGraph::linkHasInputUnity( const INodeWidget *input_unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeLinkItemDataPtr[ index ].hasInput( input_unity ) )
			return true;
	return false;
}
int NodeGraph::linkHasOutputUnity( const INodeComponent *output_unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeLinkItemDataPtr[ index ].hasOutput( output_unity ) )
			return true;
	return false;
}
int NodeGraph::linkHasOutputUnity( const INodeWidget *output_unity ) const {
	size_t count = nodeLinkItems.size( );
	if( count == 0 )
		return false;
	auto nodeLinkItemDataPtr = nodeLinkItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( nodeLinkItemDataPtr[ index ].hasOutput( output_unity ) )
			return true;
	return false;
}
int NodeGraph::linkRemoveFirstInputItem( const INodeComponent *input_unity ) {
	auto iterator = nodeLinkItems.begin( );
	auto end = nodeLinkItems.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->hasInput( input_unity ) ) {
			nodeLinkItems.erase( iterator );
			return 1;
		}
	return 0;
}
int NodeGraph::linkRemoveFirstOutputItem( const INodeComponent *output_unity ) {
	auto iterator = nodeLinkItems.begin( );
	auto end = nodeLinkItems.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->hasOutput( output_unity ) ) {
			nodeLinkItems.erase( iterator );
			return 1;
		}
	return 0;
}
int NodeGraph::linkRemoveFirstInputItem( const INodeComponent *output_unity, const INodeComponent *input_unity ) {
	auto iterator = nodeLinkItems.begin( );
	auto end = nodeLinkItems.end( );
	for( ; iterator != end; ++iterator )
		if( iterator->hasInput( input_unity ) && iterator->hasOutput( output_unity ) ) {
			nodeLinkItems.erase( iterator );
			return 1;
		}
	return 0;
}
bool NodeGraph::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	/// 累加数据
	std_vector< uint8_t > mulStdData;
	size_t count;
	std_vector< uint8_t > result;
	QList< INodeWidget * > nodeWidgets = findChildren< INodeWidget * >( );
	// 排序表达式
	auto lambda = [] ( std_pairt< INodeComponent *, size_t > &left, std_pairt< INodeComponent *, size_t > &right ) {
		return left.second < right.second;
	};
	std_vector< uint8_t > componentResult;
	uint8_t *lastPtr;
	uint8_t *data;
	std_vector_pairt< INodeComponent *, size_t > componentId;
	size_t nodeWidgetId;
	std_vector< uint8_t > nodeCompoent;
	std_vector< uchar > idData;
	size_t index;
	int64_t pos;
	qsizetype nodeWidgetCount = nodeWidgets.size( );
	qsizetype nodeWidgetIndex = 0;
	auto nodeWidgetDataPtr = nodeWidgets.data( );
	INodeWidget *nodeWidget;

	for( ; nodeWidgetIndex < nodeWidgetCount; ++nodeWidgetIndex ) {
		nodeWidget = nodeWidgetDataPtr[ nodeWidgetIndex ];
		componentId = nodeWidget->getComponentID( );
		std::ranges::sort( componentId, lambda );
		nodeCompoent.resize( 0 );
		for( auto [ component,id ] : componentId )
			if( component->getVarObject( ) != nullptr && component->getVarObject( )->serializeToVectorData( &componentResult ) ) {
				toData( id, &idData );
				nodeCompoent.append_range( idData );
				nodeCompoent.append_range( componentResult );
			}
		count = nodeCompoent.size( );
		// 追加数量 = 组件大小 + ( 组件数据量+ ID 占用 +  xy坐标)
		index = sizeof( size_t ) * 4 + count;
		lastPtr = converQMetaObjectInfoToUInt8Vector( &result, nodeWidget->metaObject( ), nodeWidget->getNodeStack( )->getStackTypeNames( ), nodeWidget->getNodeNames( ), index );
		long long i = lastPtr - result.data( );
		// 赋值节点ID
		nodeWidgetId = getNodeWidgetID( nodeWidget );
		*( size_t * ) lastPtr = nodeWidgetId;
		lastPtr += sizeof( nodeWidgetId );
		// 坐标赋值
		index = sizeof pos;
		// 赋值 x
		pos = nodeWidget->x( );
		*( decltype(pos) * ) lastPtr = pos;

		lastPtr += index;
		// 赋值 y
		pos = nodeWidget->y( );
		*( decltype(pos) * ) lastPtr = pos;
		lastPtr += index;

		// 赋值组件数据量
		*( size_t * ) lastPtr = count;
		lastPtr += sizeof( nodeWidgetId );
		// 拷贝组件数据
		data = nodeCompoent.data( );
		for( index = 0; index < count; ++index )
			lastPtr[ index ] = data[ index ];
		mulStdData.append_range( result );
	}
	count = mulStdData.size( );
	// 大小端 + (组件数量 + 总数(各个节点序列化的数据量))
	index = 1 + sizeof size_t + sizeof qsizetype;
	result_data_vector->resize( count + index );

	lastPtr = result_data_vector->data( );
	*lastPtr = isBegEndian( );
	lastPtr += 1;
	*( size_t * ) lastPtr = count;
	lastPtr += sizeof size_t;
	*( qsizetype * ) lastPtr = nodeWidgetCount;

	lastPtr = result_data_vector->data( ) + index;
	data = mulStdData.data( );
	for( index = 0; index < count; ++index )
		lastPtr[ index ] = data[ index ];
	return result_data_vector->size( );
}
size_t NodeGraph::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	std_lock_grad_mutex lockGradMutexWidget( *nodeWidgetIDMutex );
	std_lock_grad_mutex lockGradMutexComponent( *nodeComponentIDMutex );

	auto cood = *read_data_vector != isBegEndian( );
	size_t needCount = *( size_t * ) ( read_data_vector + 1 );
	if( cood )
		ISerialize::converEndian( needCount );
	// 数据头
	size_t jumpCompCount = sizeof size_t + 1;
	if( needCount > data_count ) {
		tools::debug::printError( "参考数据不满足所需数据" );
		return 0;
	}
	// 获取节点个数
	auto lastPtr = read_data_vector + jumpCompCount;
	auto nodeWidgetCount = *lastPtr;
	if( nodeWidgetCount == 0 )
		return jumpCompCount;
	size_t index;
	size_t useCount;
	size_t inheritCount;
	size_t id;
	uchar beg;
	int64_t x;
	int64_t y;
	qsizetype idIndex;
	qsizetype componentCount;
	std_vector< QString > stackNames;
	std_vector< QString > meteObjectNames;
	std_vector< QString > typeNames;
	INodeStack *nodeStack;
	INodeWidget *generateNode;
	std_vector< QString > inheritInfo;
	std_vector_pairt< INodeComponent *, size_t > componentId;
	size_t componentIdCount;
	std::pair< INodeComponent *, size_t > *componentDataPtr;
	std_shared_ptr< ITypeObject > varObject;
	std_shared_ptr< IVarStack > varStack;
	auto surplus = data_count - jumpCompCount;
	lastPtr += sizeof size_t;
	for( size_t serIndex = 0; serIndex < nodeWidgetCount; ++serIndex ) {
		useCount = ISerialize::SerializeInfo::getSerializeInfo( lastPtr, surplus, &beg, &stackNames, &meteObjectNames, &typeNames );
		if( useCount == 0 ) {
			tools::debug::printError( "无法从序列化中获取对象信息" );
			return 0;
		}
		nodeStack = INodeStack::getInstance( stackNames[ 0 ] );
		if( nodeStack == nullptr ) {
			tools::debug::printError( "无法匹配适应的节点生成器 : " + stackNames[ 0 ] );
			return 0;
		}
		generateNode = nodeStack->generateNode( typeNames[ 0 ] );
		if( generateNode == nullptr ) {
			tools::debug::printError( "无法生成对应的节点 : " + typeNames[ 0 ] );
			return 0;
		}
		inheritInfo = ISerialize::SerializeInfo::getMetaInheritInfo( generateNode->metaObject( ) );
		inheritCount = inheritInfo.size( );
		if( inheritCount != meteObjectNames.size( ) ) {
			tools::debug::printError( "节点继承关系不匹配 : " + typeNames[ 0 ] );
			return 0;
		}
		for( index = 0; index < inheritCount; ++index )
			if( meteObjectNames[ index ] != inheritInfo[ index ] ) {
				tools::debug::printError( "节点继承关系不匹配 : " + typeNames[ 0 ] );
				return 0;
			}
		// 获取 id
		lastPtr = lastPtr + useCount;

		id = *( ( size_t * ) lastPtr );
		registerID( generateNode, id );
		// 获取 x
		lastPtr += sizeof( size_t );
		x = *( ( int64_t * ) lastPtr );
		// 获取 y
		lastPtr += sizeof int64_t;
		y = *( ( int64_t * ) lastPtr );
		generateNode->move( x, y );
		// 获取组件数目
		lastPtr += sizeof int64_t;

		componentCount = *( ( qsizetype * ) lastPtr );
		lastPtr += sizeof qsizetype;
		surplus = data_count - ( lastPtr - read_data_vector );
		if( componentCount == 0 )
			continue; // 组件为 0
		id = *( ( size_t * ) lastPtr );
		if( surplus < useCount ) {
			tools::debug::printError( "数据量使用异常" );
			return 0;
		}
		surplus = surplus - useCount;
		if( id > surplus ) {
			tools::debug::printError( "数据量无法配置节点组件信息" );
			return 0;
		}
		lastPtr += sizeof size_t;
		if( id == 0 )
			continue;
		componentId = generateNode->getComponentID( );
		componentIdCount = componentId.size( );
		componentDataPtr = componentId.data( );
		if( componentIdCount != componentCount ) {
			tools::debug::printError( "节点组件不匹配，请检查节点 : " + generateNode->getNodeNames( )[ 0 ] + " 是否异常" );
			return 0;
		}

		for( idIndex = 0; componentCount < componentIdCount; ++idIndex ) {
			inheritCount = *( ( size_t * ) lastPtr );
			lastPtr += sizeof size_t;
			surplus = data_count - ( lastPtr - read_data_vector );
			for( index = 0; index < componentIdCount; ++index )
				if( componentDataPtr[ index ].second == inheritCount ) {
					varObject = componentDataPtr[ index ].first->getVarObject( );
					if( varObject != nullptr ) {
						useCount = ISerialize::SerializeInfo::getSerializeInfo( lastPtr, surplus, &beg, &stackNames, &meteObjectNames, &typeNames );
						if( useCount == 0 ) {
							tools::debug::printError( "组件id序列为 : " + QString::number( inheritCount ) + " 出现异常，请检查节点 : " + generateNode->getNodeNames( )[ 0 ] + " 是否异常" );
							return 0;
						}
						varStack = IVarStack::getInstance( stackNames[ 0 ] );
						if( varObject == nullptr ) {
							tools::debug::printError( "无法找到匹配变量堆栈 : " + stackNames[ 0 ] );
							return 0;
						}
						varObject = varStack->generateVar( typeNames[ 0 ] );
						if( varObject == nullptr ) {
							tools::debug::printError( "变量堆栈创建类型失败 : " + stackNames[ 0 ] + " ! " + typeNames[ 0 ] );
							return 0;
						}
						useCount = varObject->serializeToObjectData( lastPtr, surplus );
						if( useCount == 0 ) {
							tools::debug::printError( "变量反序列化失败 : " + stackNames[ 0 ] + " ! " + typeNames[ 0 ] );
							return 0;
						}
						lastPtr += useCount;
						componentDataPtr[ index ].first->setVar( varObject );
						lastPtr += useCount;
					}
					index = 0;
					break;
				}
			if( index != 0 ) {
				tools::debug::printError( "组件id序列为 : " + QString::number( inheritCount ) + " 出现异常，请检查节点 : " + generateNode->getNodeNames( )[ 0 ] + " 是否异常" );
				return 0;
			}
			size_t mod = lastPtr - read_data_vector;
			if( data_count < mod ) {
				tools::debug::printError( "数据量使用异常" );
				return 0;
			}
			surplus = data_count - mod;
			if( surplus == 0 )
				break;
		}
	}

	nodeComponentAdviseIDMutex->lock( );
	nodeWidgetAdviseIDMutex->lock( );
	return 0;
}
size_t NodeGraph::getNodeCompoentID( const INodeComponent *node_component ) const {
	std_lock_grad_mutex lockGradMutex( *nodeComponentIDMutex );
	size_t resultID = 0;
	if( ::getUnitySecond( nodeComponentID, node_component, &resultID ) )
		return resultID;
	return 0;
}
size_t NodeGraph::getNodeWidgetID( const INodeWidget *node_widget ) const {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	size_t resultID = 0;
	if( ::getUnitySecond( nodeWidgetID, node_widget, &resultID ) )
		return resultID;
	return 0;
}
void NodeGraph::mousePressEvent( QMouseEvent *event ) {
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
		repaint( );
		return;
	}
}
void NodeGraph::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	QPoint start, end;
	for( auto item : nodeLinkItems )
		if( item.getInputOutputPos( &start, &end ) )
			painter.drawLine( start, end );
	if( selectNodeComponent /* 绘制即时连线 */ ) {
		painter.drawLine( selectNodeComponentPoint, currentMouseInWidgetPos );
	}
}

size_t NodeGraph::registerID( INodeComponent *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeComponentIDMutex );
	return ::randomId( nodeComponentID, request_ui_ptr );
}
size_t NodeGraph::registerID( INodeWidget *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	return ::randomId( nodeWidgetID, request_ui_ptr );
}
size_t NodeGraph::registerID( INodeComponent *request_ui_ptr, size_t advise_id ) {
	size_t count = nodeComponentID.size( );
	if( count == 0 ) {
		nodeComponentID.emplace_back( request_ui_ptr, advise_id );
		return advise_id;
	}
	auto data = nodeComponentID.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].second == advise_id )
			return 0;
	nodeComponentID.emplace_back( request_ui_ptr, advise_id );
	return advise_id;
}
size_t NodeGraph::registerID( INodeWidget *request_ui_ptr, size_t advise_id ) {
	size_t count = nodeWidgetID.size( );
	if( count == 0 ) {
		nodeWidgetID.emplace_back( request_ui_ptr, advise_id );
		return advise_id;
	}
	auto data = nodeWidgetID.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].second == advise_id )
			return 0;
	nodeWidgetID.emplace_back( request_ui_ptr, advise_id );
	return advise_id;
}
size_t NodeGraph::removeId( INodeComponent *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeComponentIDMutex );
	return ::removeId( nodeComponentID, request_ui_ptr );
}
size_t NodeGraph::removeId( INodeWidget *request_ui_ptr ) {
	std_lock_grad_mutex lockGradMutex( *nodeWidgetIDMutex );
	return ::removeId( nodeWidgetID, request_ui_ptr );
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
void NodeGraph::requestNodeComponentID( INodeComponent *request_node_component_ptr ) {
	size_t id = registerID( request_node_component_ptr );
	request_node_component_ptr->registerIDFinish( id );
}
void NodeGraph::requestNodeWidgetAdviseID( INodeWidget *request_node_widget_ptr, size_t advise_id ) {
	if( nodeWidgetAdviseIDMutex.get( )->try_lock( ) ) {
		advise_id = registerID( request_node_widget_ptr, advise_id );
		nodeWidgetAdviseIDMutex->unlock( );
		request_node_widget_ptr->registerIDFinish( advise_id );
	} else
		request_node_widget_ptr->registerIDFinish( getId( nodeWidgetID, request_node_widget_ptr ) );
}
void NodeGraph::requestNodeComponentAdviseID( INodeComponent *request_node_component_ptr, size_t advise_id ) {
	if( nodeComponentAdviseIDMutex.get( )->try_lock( ) ) {
		advise_id = registerID( request_node_component_ptr, advise_id );
		nodeComponentAdviseIDMutex->unlock( );
		request_node_component_ptr->registerIDFinish( advise_id );
	} else
		request_node_component_ptr->registerIDFinish( getId( nodeComponentID, request_node_component_ptr ) );
}
void NodeGraph::destoryNodeWidgetID( INodeWidget *request_node_widget_ptr ) {
	removeId( request_node_widget_ptr );
}
void NodeGraph::destoryNodeComponentID( INodeComponent *request_node_component_ptr ) {
	removeId( request_node_component_ptr );
}
