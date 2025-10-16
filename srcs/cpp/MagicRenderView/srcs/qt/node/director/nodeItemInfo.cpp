#include "nodeItemInfo.h"

#include "../item/nodeItem.h"

#include "../nodeItemMenu/nodeItemMenu.h"
NodeItemInfo::~NodeItemInfo( ) {
	emit releaseThis( this );

	delete manageMenu;

	tools::debug::printInfo( "释放对象" );
}
NodeItemInfo::NodeItemInfo( NodeItem *node_item ) : QObject( nullptr ),
	nodeItem( node_item ) {
	manageMenu = new QMenu;
	QString title( "删除[ %1 ]节点" );
	auto addAction = manageMenu->addAction( title.arg( node_item->getMetaObjectPathName( ) ) );
	connect( addAction, &QAction::triggered, [this]( ) {
		nodeItem->deleteLater( );
	} );
}
