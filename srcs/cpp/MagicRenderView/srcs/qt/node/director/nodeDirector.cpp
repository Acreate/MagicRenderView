#include "nodeDirector.h"

#include <QPainter>
#include <QPainterPath>
#include <qmenu.h>

#include "nodeItemGenerateInfo.h"
#include "nodeItemInfo.h"
#include "nodePortLinkInfo.h"

#include "../../application/application.h"

#include "../../generate/varGenerate.h"

#include "../../widgets/mainWidget.h"

#include "../nodeItemMenu/nodeItemMenu.h"

#include "../prot/inputProt/nodeInputPort.h"

#include "../widgets/nodeItemInfoScrollAreaWidget.h"
bool NodeDirector::addManagementWidget( NodeItemInfoScrollAreaWidget *add_widget ) {
	size_t count = nodeItemInfoScrollAreaWidgets.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto data = nodeItemInfoScrollAreaWidgets.data( );
		for( ; index < count; ++index )
			if( data[ index ] == nullptr ) {
				data[ index ] = add_widget;
				return true;
			}
	}
	nodeItemInfoScrollAreaWidgets.emplace_back( add_widget );
	connect( add_widget, &QWidget::destroyed, [add_widget, this]( ) {
		removeManagementWidget( add_widget );
	} );
	return true;
}
bool NodeDirector::removeManagementWidget( NodeItemInfoScrollAreaWidget *del_widget ) {
	size_t count = nodeItemInfoScrollAreaWidgets.size( );
	if( count != 0 ) {
		size_t index = 0;
		auto data = nodeItemInfoScrollAreaWidgets.data( );
		for( ; index < count; ++index )
			if( data[ index ] == del_widget ) {
				data[ index ] = nullptr;
				return true;
			}
	}
	return false;
}
NodeDirector::NodeDirector( QObject *parent ) : QObject( parent ) {
}
NodeItemInfoScrollAreaWidget * NodeDirector::requestGetNodeEditorWidget( const type_info &request_type, NodeItem *request_node_item_ptr ) {
	return nullptr;
}
bool NodeDirector::linkInstallPort( NodePort *first_port, NodePort *scond_port ) {
	if( first_port == nullptr || scond_port == nullptr || scond_port == first_port )
		return false; // 同一个节点或者为 nullptr
	bool firstIsOutputPort = first_port->isOutputPort( );
	bool scondIsOutputPort = scond_port->isOutputPort( );
	if( firstIsOutputPort == scondIsOutputPort )
		return false; // 同是同一类型，则返回
	if( firstIsOutputPort )
		return linkInstallPort( ( NodeInputPort * ) scond_port, ( NodeOutputPort * ) first_port );
	else
		return linkInstallPort( ( NodeInputPort * ) first_port, ( NodeOutputPort * ) scond_port );

}
bool NodeDirector::linkUnInstallPort( NodePort *first_port, NodePort *scond_port ) {
	if( first_port == nullptr || scond_port == nullptr || scond_port == first_port )
		return false; // 同一个节点或者为 nullptr
	bool firstIsOutputPort = first_port->isOutputPort( );
	bool scondIsOutputPort = scond_port->isOutputPort( );
	if( firstIsOutputPort == scondIsOutputPort )
		return false; // 同是同一类型，则返回
	if( firstIsOutputPort )
		return linkUnInstallPort( ( NodeInputPort * ) scond_port, ( NodeOutputPort * ) first_port );
	else
		return linkUnInstallPort( ( NodeInputPort * ) first_port, ( NodeOutputPort * ) scond_port );
}
bool NodeDirector::linkInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port ) {
	if( input_port == nullptr || output_port == nullptr )
		return false; // 同一个节点或者为 nullptr
	NodeItem *nodeItem = input_port->parentItem;
	if( nodeItem == output_port->parentItem )
		return false; // 同一个节点或者为 nullptr
	const I_Type *inputPorVarType = input_port->getVarType( );
	if( inputPorVarType == nullptr ) {
		tools::debug::printError( QString( "%1 输入端口不存在变量指向" ).arg( input_port->getMetaObjectPathName( ) ) );
		return false;
	}

	const I_Type *outputPorVarType = output_port->getVarType( );
	if( outputPorVarType == nullptr ) {
		tools::debug::printError( QString( "%1 输出端口不存在变量指向" ).arg( output_port->getMetaObjectPathName( ) ) );
		return false;
	}

	if( varGenerate->supportType( inputPorVarType->getTypeInfo( ), outputPorVarType->getTypeInfo( ) ) == false )
		return false;

	size_t count = linkVectorPairt.size( );
	auto data = linkVectorPairt.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ]->inputPort == input_port )
			return data[ index ]->link( output_port );
	// 没有链接对象就创建
	auto newLinkObjPtr = new NodePortLinkInfo( input_port );
	newLinkObjPtr->link( output_port );
	linkVectorPairt.emplace_back( newLinkObjPtr );
	// 节点删除则释放
	connect( nodeItem, &NodeItem::releaseThiNodeItem, [this] ( NodeItem *release_node_item ) {
		size_t count = linkVectorPairt.size( );
		auto data = linkVectorPairt.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ]->inputPort->getParentItem( ) == release_node_item ) {
				delete data[ index ];
				linkVectorPairt.erase( linkVectorPairt.begin( ) + index );
				break;
			}
	} );
	connect( newLinkObjPtr, &NodePortLinkInfo::linkNodePort, [this] ( NodePortLinkInfo *sender_obj_ptr, NodeInputPort *input_port, NodeOutputPort *output_port ) {
		emit linkNodePort( this, sender_obj_ptr, input_port, output_port );
	} );
	connect( newLinkObjPtr, &NodePortLinkInfo::unlinkNodePort, [this] ( NodePortLinkInfo *sender_obj_ptr, NodeInputPort *input_port, NodeOutputPort *output_port ) {
		emit unlinkNodePort( this, sender_obj_ptr, input_port, output_port );
	} );

	return true;
}
bool NodeDirector::linkUnInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port ) {
	if( input_port == nullptr || output_port == nullptr || input_port->parentItem == output_port->parentItem )
		return false; // 同一个节点或者为 nullptr

	size_t count = linkVectorPairt.size( );
	if( count == 0 )
		return false;// 不存在匹配的链接端
	auto pair = linkVectorPairt.data( );
	for( size_t index = 0; index < count; ++index )
		if( pair[ index ]->inputPort == input_port )
			return pair[ index ]->unLink( output_port );
	return false; // 不存在
}
size_t NodeDirector::run( ) {
	return 0;
}
bool NodeDirector::setRaise( const NodeItem *raise_node_item ) {

	// 节点个数
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return false;

	// 节点数组指针
	auto data = generateNodeItems.data( );
	// 下标
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] != nullptr && data[ index ]->nodeItem == raise_node_item ) {
			count -= 1;
			if( index == count )
				return true;
			auto *makeItem = data[ index ];
			for( ; index < count; index++ )
				data[ index ] = data[ index + 1 ];
			data[ index ] = makeItem;
			return true; // 检测到了
		}
	return false;
}
bool NodeDirector::setRaise( const NodePort *raise_node_port ) {
	return setRaise( raise_node_port->parentItem );
}
NodeItem * NodeDirector::getLastNodeItem( ) {
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return nullptr;
	return generateNodeItems.data( )[ count - 1 ]->nodeItem;
}
void NodeDirector::draw( QPainter &painter_target ) const {

	size_t count = generateNodeItems.size( );
	size_t index = 0;
	if( count > 0 ) {
		auto data = generateNodeItems.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				NodeItem *nodeItem = data[ index ]->nodeItem;
				if( nodeItem == nullptr )
					continue;
				painter_target.drawImage( nodeItem->getPos( ), *nodeItem->getNodeItemRender( ) );
			}
	}

	count = linkVectorPairt.size( );
	if( count > 0 ) {
		QPoint inport;
		QPoint outport;
		size_t outIndex;

		auto nodePortLinkInfo = linkVectorPairt.data( );
		index = 0;
		size_t outPortCount;
		std::pair< NodeOutputPort *, QAction * > *outPortData;
		for( ; index < count; ++index )
			if( outPortCount = nodePortLinkInfo[ index ]->outputPorts.size( ), nodePortLinkInfo[ index ]
				!= nullptr && outPortCount != 0 ) {
				nodePortLinkInfo[ index ]->inputPort->getPos( outport );
				outPortData = nodePortLinkInfo[ index ]->outputPorts.data( );
				for( outIndex = 0; outIndex < outPortCount; ++outIndex ) {
					outPortData[ outIndex ].first->getPos( inport );
					painter_target.drawLine( outport, inport );
					qDebug( ) << outport << " -> " << inport;
				}
			}
	}
}
std_vector< NodeItem * > NodeDirector::getNodeItems( ) const {
	std_vector< NodeItem * > result;
	size_t count = generateNodeItems.size( );
	auto data = generateNodeItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] != nullptr )
			result.emplace_back( data[ index ]->nodeItem );
	return result;
}

std_vector< QImage * > NodeDirector::getNodeItemRenders( ) const {
	std_vector< QImage * > result;
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return result;
	auto data = generateNodeItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] != nullptr )
			result.emplace_back( data[ index ]->nodeItem->getNodeItemRender( ) );
	return result;
}
bool NodeDirector::remove( NodeItem *remove_node_item ) {
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return false;
	auto data = generateNodeItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] != nullptr && data[ index ]->nodeItem == remove_node_item ) {
			emit releaseNodeItemInfoObj( data[ index ] );
			data[ index ] = nullptr;
			return true;
		}
	return false;
}
bool NodeDirector::release( NodePort *remove_node_port ) {
	return release( remove_node_port->parentItem );
}
bool NodeDirector::createMenu( ) {

	auto infos = varGenerate->getNodeItemSortMap( );
	if( infos.size( ) == 0 )
		return false;
	QString enumString;
	for( auto &[ enumType,dirNamMap ] : infos ) {
		if( NodeItem::getEnumName( enumType, enumString ) == false )
			continue;
		QMenu *nodeTypeMenu = nodeItemCreateMenu->addMenu( enumString );
		for( auto &[ dir,nameMap ] : dirNamMap ) {
			QMenu *dirMenu = nodeTypeMenu->addMenu( dir );
			for( auto &[ className, typePtr ] : nameMap ) {
				if( className.isEmpty( ) )
					continue;
				auto addAction = dirMenu->addAction( className );
				auto nodeItemGenerateInfo = std_shared_ptr< NodeItemGenerateInfo >( new NodeItemGenerateInfo( dir, className, typePtr ) );
				generateNodeItemInfos.emplace_back( nodeItemGenerateInfo );
				connect( addAction, &QAction::triggered, [this, dir, className, typePtr]( ) {
					if( createNodeItem( dir, className, typePtr ) == nullptr || mainWidget == nullptr )
						return;
					mainWidget->update( );
				} );
			}
		}
	}
	return true;
}
bool NodeDirector::resetMenu( QObject *del_ptr ) {
	nodeItemCreateMenu = new NodeItemMenu( );
	return this->createMenu( );
}
bool NodeDirector::realseNodeItemInfo( NodeItemInfo *del_ptr ) {
	return remove( del_ptr->nodeItem );
}
bool NodeDirector::release( const NodeItem *remove_node_item ) {
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return false;
	auto data = generateNodeItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] != nullptr && data[ index ]->nodeItem == remove_node_item ) {
			auto *item = data[ index ];
			emit releaseNodeItemInfoObj( item );
			data[ index ] = nullptr;
			NodeItem *nodeItem = item->nodeItem;
			nodeItem->disconnect( this );
			delete item;
			return true;
		}
	return false;
}
bool NodeDirector::setContentWidget( MainWidget *main_widget ) {
	if( main_widget == nullptr )
		return false;
	if( mainWidget == main_widget )
		return true;
	generateNodeItemInfos.clear( );
	auto clone = generateNodeItems;
	generateNodeItems.clear( );
	for( auto removeItem : clone )
		if( removeItem )
			delete removeItem->nodeItem;

	mainWidget = main_widget;
	applicationInstancePtr = Application::getApplicationInstancePtr( );

	varGenerate = applicationInstancePtr->getVarGenerate( );
	if( nodeItemCreateMenu )
		delete nodeItemCreateMenu;
	nodeItemCreateMenu = new NodeItemMenu( );
	connect( nodeItemCreateMenu, &QMenu::destroyed, this, &NodeDirector::resetMenu );

	return this->createMenu( );;
}

NodeItem * NodeDirector::createNodeItem( const QString &dir_name, const QString &node_name, const std_shared_ptr< I_Type > &itype_ptr ) {
	NodeItem *nodeItem = ( NodeItem * ) itype_ptr->getCreate( ).operator()( );
	if( nodeItem == nullptr )
		return nullptr;
	if( appendNodeItem( nodeItem ) )
		return nodeItem;
	delete nodeItem;
	return nullptr;
}

size_t NodeDirector::appendNodeItem( NodeItem *new_node_item ) {

	new_node_item->setMainWidget( mainWidget );
	if( new_node_item->intPortItems( mainWidget ) == false )
		return 0;
	size_t count = generateNodeItems.size( );
	auto data = generateNodeItems.data( );
	size_t index = 0;
	NodeItemInfo *nodeItemInfo = new NodeItemInfo( new_node_item );
	connect( nodeItemInfo, &NodeItemInfo::releaseThis, this, &NodeDirector::realseNodeItemInfo );
	for( ; index < count; ++index )
		if( data[ index ] == nullptr ) {
			data[ index ] = nodeItemInfo;
			break;
		}
	if( index == count ) {
		generateNodeItems.emplace_back( nodeItemInfo );
		++count;
		data = generateNodeItems.data( ); // 更新基址
	}
	size_t checkCode = count;
	for( ; index < count; ++index )
		if( data[ index ]->nodeItem->generateCode != ( index + 1 ) ) { // 掉链子了
			checkCode = index + 1;
			index = 0; // 重新遍历
			for( ; index < count; ++index )
				if( data[ index ]->nodeItem->generateCode == checkCode ) {
					index = checkCode + 1;
					checkCode = count;
					break;
				}
			if( index == count )
				break;

		}
	new_node_item->generateCode = checkCode;
	new_node_item->move( mainWidget->mapFromGlobal( nodeItemCreateMenu->pos( ) ) );
	connect( new_node_item, &NodeItem::releaseThiNodeItem, this, &NodeDirector::remove );

	return new_node_item->generateCode;
}
bool NodeDirector::getLinkOutPorts( const NodeInputPort *input_port, std_vector< NodeOutputPort * > &result_vector ) const {
	size_t count = linkVectorPairt.size( );
	auto data = linkVectorPairt.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->inputPort == input_port ) {
			result_vector = data[ index ]->getOutputPorts( );
			return true;
		}
	return false;
}
bool NodeDirector::getLinkOutPorts( const NodePort *input_port, std_vector< NodeOutputPort * > &result_vector ) const {
	if( input_port->isOutputPort( ) == false )
		return getLinkOutPorts( ( NodeInputPort * ) input_port, result_vector );
	return false;
}
bool NodeDirector::getLinkControlMenu( const NodePort *input_port, QMenu *&result_menu_ptr ) const {
	if( input_port->isOutputPort( ) == false )
		return getLinkControlMenu( ( NodeInputPort * ) input_port, result_menu_ptr );
	return false;
}
bool NodeDirector::getLinkControlMenu( const NodeInputPort *input_port, QMenu *&result_menu_ptr ) const {
	size_t count = linkVectorPairt.size( );
	auto data = linkVectorPairt.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->inputPort == input_port ) {
			result_menu_ptr = data[ index ]->removeLinkMenu;
			return true;
		}
	return false;
}
bool NodeDirector::getItemManageMenu( const NodeItem *node_item_ptr, QMenu *&result_menu_ptr ) {
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return false;
	auto data = generateNodeItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] != nullptr && data[ index ]->nodeItem == node_item_ptr ) {
			result_menu_ptr = data[ index ]->manageMenu;
			return true;
		}
	return false;
}

NodeDirector::~NodeDirector( ) {
	emit releaseThis( this );
	size_t count = nodeItemInfoScrollAreaWidgets.size( );
	size_t index;
	if( count ) {
		index = 0;
		auto data = nodeItemInfoScrollAreaWidgets.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr )
				delete data[ index ];
	}

	count = generateNodeItems.size( );
	if( count ) {
		index = 0;
		auto data = generateNodeItems.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				NodeItem *nodeItem = data[ index ]->nodeItem;
				NodeItemInfo *nodeItemInfo = data[ index ];
				data[ index ] = nullptr;
				delete nodeItem;
			}
	}

	nodeItemCreateMenu->disconnect( nodeItemCreateMenu, &QMenu::destroyed, this, &NodeDirector::resetMenu );
	delete nodeItemCreateMenu;
}

bool NodeDirector::getNodeItemRender( QImage &result_render_image, const QPoint &offset ) const {
	return true;
}
NodeItem::Click_Type NodeDirector::getClickNodeItem( NodeItem *&result_node_item, NodePort * &result_node_port ) {
	return getClickNodeItem( mainWidget->mapFromGlobal( QCursor::pos( ) ), result_node_item, result_node_port );
}
NodeItem::Click_Type NodeDirector::getClickNodeItem( const QPoint &click_pos, NodeItem *&result_node_item, NodePort * &result_node_port ) {

	result_node_item = nullptr;
	result_node_port = nullptr;
	// 节点个数
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return NodeItem::Click_Type::None;
	// 节点数组指针
	auto data = generateNodeItems.data( );
	// 下标
	size_t index = 0;
	// 局部坐标
	QPoint localPoint;

	for( ; index < count; ++index )
		if( data[ index ] != nullptr ) {
			localPoint = click_pos - data[ index ]->nodeItem->getPos( );
			NodeItem::Click_Type pointType = data[ index ]->nodeItem->relativePointType( localPoint );
			if( pointType == NodeItem::Click_Type::None )
				continue; // 空白处，则跳过循环
			result_node_item = data[ index ]->nodeItem; // 选中了非空白处
			switch( pointType ) {
				case NodeItem::Click_Type::InputPort :
					result_node_port = data[ index ]->nodeItem->getNodeInputAtRelativePointType( localPoint );
					break;
				case NodeItem::Click_Type::OutputPort :
					result_node_port = data[ index ]->nodeItem->getNodeOutputPortAtRelativePointType( localPoint );
					break;
				default :
					result_node_port = nullptr;
					break;
			}

			return pointType; // 检测到了
		}

	return NodeItem::Click_Type::None;
}
NodeItem::Click_Type NodeDirector::getClickNodeItemInputPort( NodeItem *&result_node_item, NodeInputPort *&result_node_port ) {
	return getClickNodeItemInputPort( mainWidget->mapFromGlobal( QCursor::pos( ) ), result_node_item, result_node_port );
}
NodeItem::Click_Type NodeDirector::getClickNodeItemInputPort( const QPoint &click_pos, NodeItem *&result_node_item, NodeInputPort *&result_node_port ) {

	result_node_item = nullptr;
	result_node_port = nullptr;
	// 节点个数
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return NodeItem::Click_Type::None;
	// 节点数组指针
	auto data = generateNodeItems.data( );
	// 下标
	size_t index = 0;
	// 局部坐标
	QPoint localPoint;

	for( ; index < count; ++index )
		if( data[ index ] != nullptr ) {
			localPoint = click_pos - data[ index ]->nodeItem->getPos( );
			NodeItem::Click_Type pointType = data[ index ]->nodeItem->relativePointType( localPoint );
			if( pointType == NodeItem::Click_Type::None )
				continue; // 空白处，则跳过循环
			result_node_item = data[ index ]->nodeItem; // 选中了非空白处
			switch( pointType ) {
				case NodeItem::Click_Type::InputPort :
					result_node_port = data[ index ]->nodeItem->getNodeInputAtRelativePointType( localPoint );
					break;
				default :
					result_node_port = nullptr;
					break;
			}

			return pointType; // 检测到了
		}
	return NodeItem::Click_Type::None;
}
NodeItem::Click_Type NodeDirector::getClickNodeItemOutputPort( NodeItem *&result_node_item, NodeOutputPort *&result_node_port ) {
	return getClickNodeItemOutputPort( mainWidget->mapFromGlobal( QCursor::pos( ) ), result_node_item, result_node_port );
}
NodeItem::Click_Type NodeDirector::getClickNodeItemOutputPort( const QPoint &click_pos, NodeItem *&result_node_item, NodeOutputPort *&result_node_port ) {
	result_node_item = nullptr;
	result_node_port = nullptr;
	// 节点个数
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return NodeItem::Click_Type::None;
	// 节点数组指针
	auto data = generateNodeItems.data( );
	// 下标
	size_t index = 0;
	// 局部坐标
	QPoint localPoint;

	for( ; index < count; ++index )
		if( data[ index ] != nullptr ) {
			localPoint = click_pos - data[ index ]->nodeItem->getPos( );
			NodeItem::Click_Type pointType = data[ index ]->nodeItem->relativePointType( localPoint );
			if( pointType == NodeItem::Click_Type::None )
				continue; // 空白处，则跳过循环
			result_node_item = data[ index ]->nodeItem; // 选中了非空白处
			switch( pointType ) {
				case NodeItem::Click_Type::OutputPort :
					result_node_port = data[ index ]->nodeItem->getNodeOutputPortAtRelativePointType( localPoint );
					break;
				default :
					result_node_port = nullptr;
					break;
			}

			return pointType; // 检测到了
		}
	return NodeItem::Click_Type::None;
}
