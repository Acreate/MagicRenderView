#include "nodeDirector.h"

#include <QPainter>
#include <QPainterPath>
#include <qmenu.h>

#include "../../application/application.h"

#include "../../generate/varGenerate.h"

#include "../../widgets/mainWidget.h"

#include "../nodeItemMenu/nodeItemMenu.h"

#include "../prot/inputProt/nodeInputPort.h"

#include "../widgets/nodeItemInfoScrollAreaWidget.h"
NodeItem * NodeDirector::NodeItemGenerateInfo::createNodeItem( const QString &dir_name, const QString &node_name ) {
	bool cond = dirName == dir_name && nodeName == node_name;
	if( cond == true )
		return ( NodeItem * ) createTypeInstancePtr.get( )->getCreate( ).operator()( );
	return nullptr;
}
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
bool NodeDirector::linkInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port ) {
	return false;
}
bool NodeDirector::linkUnInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port ) {
	return false;
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
		if( data[ index ] == raise_node_item ) {
			count -= 1;
			if( index == count )
				return true;
			NodeItem *makeItem = data[ index ];
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
void NodeDirector::draw( QPainter &painter_target ) const {
	QPainterPath painterPath;

	size_t count = generateNodeItems.size( );
	auto data = generateNodeItems.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		NodeItem *nodeItem = data[ index ];
		if( nodeItem == nullptr )
			continue;
		painter_target.drawImage( nodeItem->getPos( ), *nodeItem->getNodeItemRender( ) );
		auto pairs = nodeItem->getLinkPort( );
		for( auto &item : pairs ) {
			int first = item.first.second.first;
			int second = item.first.second.second;
			int x = item.second.second.first;
			int y = item.second.second.second;

			painterPath.moveTo( first, second );
			painterPath.lineTo( x, y );
		}
	}
	painter_target.drawPath( painterPath );
}

std_vector< QImage * > NodeDirector::getNodeItemRenders( ) const {
	std_vector< QImage * > result;
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return result;
	auto data = generateNodeItems.data( );
	for( size_t index = 0; index < count; ++index )
		result.emplace_back( data[ index ]->getNodeItemRender( ) );
	return result;
}
bool NodeDirector::remove( NodeItem *remove_node_item ) {
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return false;
	auto data = generateNodeItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == remove_node_item ) {
			data[ index ] = nullptr;
			return true;
		}
	return false;
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
bool NodeDirector::release( const NodeItem *remove_node_item ) {
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return false;
	auto data = generateNodeItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == remove_node_item ) {
			NodeItem *item = data[ index ];
			data[ index ] = nullptr;
			item->disconnect( this );
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
		delete removeItem;

	mainWidget = main_widget;
	applicationInstancePtr = Application::getApplicationInstancePtr( );

	varGenerate = applicationInstancePtr->getVarGenerate( );
	if( nodeItemCreateMenu )
		delete nodeItemCreateMenu;
	nodeItemCreateMenu = new NodeItemMenu( );
	connect( nodeItemCreateMenu, &QMenu::destroyed, [this]( ) {
		nodeItemCreateMenu = new NodeItemMenu( );
		this->createMenu( );
	} );

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
	for( ; index < count; ++index )
		if( data[ index ] == nullptr ) {
			data[ index ] = new_node_item;
			break;
		}
	if( index == count ) {
		generateNodeItems.emplace_back( new_node_item );
		++count;
		data = generateNodeItems.data( ); // 更新基址
	}
	size_t checkCode = count;
	for( ; index < count; ++index )
		if( data[ index ]->generateCode != ( index + 1 ) ) { // 掉链子了
			checkCode = index + 1;
			index = 0; // 重新遍历
			for( ; index < count; ++index )
				if( data[ index ]->generateCode == checkCode ) {
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

NodeDirector::~NodeDirector( ) {
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
			if( data[ index ] != nullptr )
				delete data[ index ];
	}

	nodeItemCreateMenu->disconnect( );
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
			localPoint = click_pos - data[ index ]->getPos( );
			NodeItem::Click_Type pointType = data[ index ]->relativePointType( localPoint );
			if( pointType == NodeItem::Click_Type::None )
				continue; // 空白处，则跳过循环
			result_node_item = data[ index ]; // 选中了非空白处
			switch( pointType ) {
				case NodeItem::Click_Type::InputPort :
					result_node_port = data[ index ]->getNodeInputAtRelativePointType( localPoint );
					break;
				case NodeItem::Click_Type::OutputPort :
					result_node_port = data[ index ]->getNodeOutputPortAtRelativePointType( localPoint );
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
			localPoint = click_pos - data[ index ]->getPos( );
			NodeItem::Click_Type pointType = data[ index ]->relativePointType( localPoint );
			if( pointType == NodeItem::Click_Type::None )
				continue; // 空白处，则跳过循环
			result_node_item = data[ index ]; // 选中了非空白处
			switch( pointType ) {
				case NodeItem::Click_Type::InputPort :
					result_node_port = data[ index ]->getNodeInputAtRelativePointType( localPoint );
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
			localPoint = click_pos - data[ index ]->getPos( );
			NodeItem::Click_Type pointType = data[ index ]->relativePointType( localPoint );
			if( pointType == NodeItem::Click_Type::None )
				continue; // 空白处，则跳过循环
			result_node_item = data[ index ]; // 选中了非空白处
			switch( pointType ) {
				case NodeItem::Click_Type::OutputPort :
					result_node_port = data[ index ]->getNodeOutputPortAtRelativePointType( localPoint );
					break;
				default :
					result_node_port = nullptr;
					break;
			}

			return pointType; // 检测到了
		}
	return NodeItem::Click_Type::None;
}
