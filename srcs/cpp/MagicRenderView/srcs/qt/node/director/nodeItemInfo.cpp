#include "nodeItemInfo.h"

#include <qt/node/item/nodeItem.h>
#include <qt/node/nodeItemMenu/nodeItemMenu.h>
NodeItemInfo::~NodeItemInfo( ) {
	emit releaseThisPtr( this );
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
bool NodeItemInfo::appendOutputNodeItemInfo( NodeItemInfo *output_ref_ptr ) {
	size_t count = outputNodeItemVector.size( );
	if( count != 0 ) {
		auto data = outputNodeItemVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr && data[ index ]->nodeItem == output_ref_ptr->nodeItem )
				return true;
		index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == nullptr ) {
				data[ index ] = output_ref_ptr;
				emit nodeItemInfoRefChangeOutputNodeItem( this );
				return true;
			}
	}
	emit nodeItemInfoRefChangeOutputNodeItem( this );
	outputNodeItemVector.emplace_back( output_ref_ptr );
	return true;
}
bool NodeItemInfo::removeOutputNodeItemInfo( NodeItemInfo *output_ref_ptr ) {

	size_t count = outputNodeItemVector.size( );
	if( count != 0 ) {
		auto data = outputNodeItemVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr && data[ index ]->nodeItem == output_ref_ptr->nodeItem ) {
				data[ index ] = nullptr;
				emit nodeItemInfoRefChangeOutputNodeItem( this );
				return true;
			}
	}
	return false;
}
bool NodeItemInfo::inOutputNodeItemInfo( NodeItem *output_ref_ptr ) const {

	size_t count = outputNodeItemVector.size( );
	if( count != 0 ) {
		auto data = outputNodeItemVector.data( );
		size_t index = 0;
		using buffVector = decltype(outputNodeItemVector);
		buffVector subVector, subBufferVector;
		for( ; index < count; ++index )
			if( data[ index ]->nodeItem == output_ref_ptr )
				return true;
			else
				subVector.append_range( data[ index ]->outputNodeItemVector );
		do {
			count = subVector.size( );
			if( count == 0 )
				return false;
			data = subVector.data( );
			index = 0;
			for( ; index < count; ++index )
				if( data[ index ]->nodeItem == output_ref_ptr )
					return true;
				else
					subBufferVector.append_range( data[ index ]->outputNodeItemVector );
			subVector = subBufferVector;
		} while( true );

	}
	return false;

}
bool NodeItemInfo::inOutputNodeItemInfo( NodeItemInfo *output_ref_ptr ) const {
	return inOutputNodeItemInfo( output_ref_ptr->nodeItem );
}
bool NodeItemInfo::appendInputNodeItemInfo( NodeItemInfo *input_ref_ptr ) {
	size_t count = inputNodeItemInfoVector.size( );
	if( count != 0 ) {
		auto data = inputNodeItemInfoVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr && data[ index ]->nodeItem == input_ref_ptr->nodeItem )
				return true;
		index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == nullptr ) {
				data[ index ] = input_ref_ptr;
				emit nodeItemInfoRefChangeInputNodeItem( this );
				return true;
			}
	}
	emit nodeItemInfoRefChangeInputNodeItem( this );
	inputNodeItemInfoVector.emplace_back( input_ref_ptr );
	return true;
}
bool NodeItemInfo::removeInputNodeItemInfo( NodeItemInfo *input_ref_ptr ) {
	size_t count = inputNodeItemInfoVector.size( );
	if( count != 0 ) {
		auto data = inputNodeItemInfoVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] != nullptr && data[ index ]->nodeItem == input_ref_ptr->nodeItem ) {
				data[ index ] = nullptr;
				emit nodeItemInfoRefChangeInputNodeItem( this );
				return true;
			}
	}
	return false;
}
bool NodeItemInfo::inInputNodeItemInfo( NodeItem *input_ref_ptr ) const {
	size_t count = inputNodeItemInfoVector.size( );
	if( count != 0 ) {
		auto data = inputNodeItemInfoVector.data( );
		size_t index = 0;
		using buffVector = decltype(inputNodeItemInfoVector);
		buffVector subVector, subBufferVector;
		for( ; index < count; ++index )
			if( data[ index ]->nodeItem == input_ref_ptr )
				return true;
			else
				subVector.append_range( data[ index ]->inputNodeItemInfoVector );
		do {
			count = subVector.size( );
			if( count == 0 )
				return false;
			data = subVector.data( );
			index = 0;
			for( ; index < count; ++index )
				if( data[ index ]->nodeItem == input_ref_ptr )
					return true;
				else
					subBufferVector.append_range( data[ index ]->inputNodeItemInfoVector );
			subVector = subBufferVector;
		} while( true );

	}
	return false;
}
bool NodeItemInfo::inInputNodeItemInfo( NodeItemInfo *input_ref_ptr ) const {
	return inInputNodeItemInfo( input_ref_ptr->nodeItem );
}
bool NodeItemInfo::getNodeItemType( nodeItemEnum::Node_Item_Type &result ) {
	result = nodeItem->getNodeMetaType( );
	return true;
}
