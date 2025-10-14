#include "nodeDirector.h"

#include <qmenu.h>

#include "../../application/application.h"

#include "../../generate/varGenerate.h"

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
bool NodeDirector::setContentWidget( MainWidget *main_widget ) {
	if( main_widget == nullptr )
		return false;
	if( mainWidget == main_widget )
		return true;
	generateNodeItemInfos.clear( );
	lastActiveNodeItem = nullptr;
	auto clone = generateNodeItems;
	generateNodeItems.clear( );
	for( auto removeItem : clone )
		delete removeItem;

	mainWidget = main_widget;
	applicationInstancePtr = Application::getApplicationInstancePtr( );

	varGenerate = applicationInstancePtr->getVarGenerate( );
	if( nodeItemCreateMenu )
		delete nodeItemCreateMenu;
	nodeItemCreateMenu = new QMenu( );

	auto infos = varGenerate->getNodeItemSortMap( );
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
					createNodeItem( dir, className, typePtr );
				} );
			}
		}
	}

	return true;
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
	connect( new_node_item, &NodeItem::releaseThiNodeItem, [this] ( NodeItem *release_node_item ) {
				size_t count = generateNodeItems.size( );
				if( count == 0 )
					return;
				auto data = generateNodeItems.data( );
				size_t index = 0;
				for( ; index < count; ++index )
					if( data[ index ] == release_node_item ) {
						data[ index ] = nullptr;
						break;
					}
			}
		);
	lastActiveNodeItem = new_node_item;
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

	if( nodeItemCreateMenu )
		delete nodeItemCreateMenu;
}

bool NodeDirector::getNodeItemRender( QImage &result_render_image, const QPoint &offset ) const {
	return true;
}
NodeItem::Click_Type NodeDirector::getClickNodeItem( NodeItem *&result_node_item ) {
	return getClickNodeItem( mainWidget->mapFromGlobal( QCursor::pos( ) ), result_node_item );
}
NodeItem::Click_Type NodeDirector::getClickNodeItem( const QPoint &click_pos, NodeItem *&result_node_item ) {

	size_t count = generateNodeItems.size( );
	auto data = generateNodeItems.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr ) {

			break;
		}

	return NodeItem::Click_Type::None;
}
