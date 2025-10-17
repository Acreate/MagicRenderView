#include "nodeItemInfo.h"

#include <qt/node/item/nodeItem.h>
#include <qt/node/nodeItemMenu/nodeItemMenu.h>
NodeItemInfo::~NodeItemInfo( ) {
	emit releaseThis( this );
	delete manageMenu;
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
bool NodeItemInfo::linkThis( NodeItemInfo *link_target ) {
	size_t count = linkInfoVector.size( );
	if( count != 0 ) {
		auto data = linkInfoVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ]->nodeItem == link_target->nodeItem )
				return true;
		index = 0;
		for( ; index < count; ++index )
			if( data[ index ]->nodeItem == nullptr ) {
				data[ index ] = link_target;
				return true;
			}
	}
	linkInfoVector.emplace_back( link_target );
	return true;
}
bool NodeItemInfo::unlinkThis( NodeItemInfo *link_target ) {

	size_t count = linkInfoVector.size( );
	if( count != 0 ) {
		auto data = linkInfoVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ]->nodeItem == link_target->nodeItem ) {
				data[ index ] = nullptr;
				return true;
			}
	}
	return false;
}
bool NodeItemInfo::inLinkHasNodeItem( NodeItem *link_target ) const {

	size_t count = linkInfoVector.size( );
	if( count != 0 ) {
		auto data = linkInfoVector.data( );
		size_t index = 0;
		using buffVector = decltype(linkInfoVector);
		buffVector subVector, subBufferVector;
		for( ; index < count; ++index )
			if( data[ index ]->nodeItem == link_target ) {
				subVector.append_range( data[ index ]->linkInfoVector );
				return true;
			}
		do {
			count = subVector.size( );
			if( count == 0 )
				return false;
			data = subVector.data( );
			index = 0;
			for( ; index < count; ++index )
				if( data[ index ]->nodeItem == link_target ) {
					subBufferVector.append_range( data[ index ]->linkInfoVector );
					return true;
				}
			subVector = subBufferVector;
		} while( true );

	}
	return false;

}
bool NodeItemInfo::inLinkHasNodeItem( NodeItemInfo *link_target ) const {
	return inLinkHasNodeItem( link_target->nodeItem );
}
bool NodeItemInfo::getNodeItemType( nodeItemEnum::Node_Item_Type &result ) {
	result = nodeItem->getNodeMetaType( );
	return true;
}
