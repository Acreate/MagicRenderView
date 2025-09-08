#include "./nodeRunFunctionSequenceItem.h"

#include "../widgets/NodeRunFunctionSequenceItemRnderWidget.h"
#include "../widgets/NodeRunSequenceItemWidget.h"
NodeRunFunctionSequenceItem::NodeRunFunctionSequenceItem( NodeRunSequenceWidget *run_sequence_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, NodeRunFunctionSequenceItem *top_layer_item ) : topLayerItem( top_layer_item ), functionDeclaration( function_declaration ), runMainSequenceWidget( run_sequence_widget ) {
	if( functionDeclaration )
		renderCurrentNodeWidget = new NodeRunFunctionSequenceItemRnderWidget( this );
	else
		renderCurrentNodeWidget = nullptr;
	renderSubItemsNodeWidget = new NodeRunSequenceItemWidget( this );
}
NodeRunFunctionSequenceItem::~NodeRunFunctionSequenceItem( ) {
	if( topLayerItem != nullptr ) {
		auto begin = topLayerItem->subItems.begin( );
		auto end = topLayerItem->subItems.end( );
		for( ; begin != end; ++begin )
			if( *begin == this ) {
				topLayerItem->subItems.erase( begin );
				break;
			}
		emit topLayerItem->subItemChange( );
		topLayerItem = nullptr;
	}
	if( renderCurrentNodeWidget )
		delete renderCurrentNodeWidget;
	for( auto &item : subItems ) {
		item->topLayerItem = nullptr;
		delete item;
	}
	if( renderCurrentNodeWidget )
		delete renderSubItemsNodeWidget;
	currentItemRemove( this );
}
bool NodeRunFunctionSequenceItem::insertBefore( NodeRunFunctionSequenceItem *insert_item ) {
	if( topLayerItem == nullptr )
		return false;
	auto begin = topLayerItem->subItems.begin( );
	auto end = topLayerItem->subItems.end( );
	for( ; begin != end; ++begin )
		if( *begin == this ) {
			if( begin == end )
				topLayerItem->subItems.insert( ++begin, insert_item );
			else
				topLayerItem->subItems.insert( begin, insert_item );
			emit topLayerItem->subItemChange( );
			return true;
		}
	return false;

}
bool NodeRunFunctionSequenceItem::insertAfter( NodeRunFunctionSequenceItem *insert_item ) {
	if( topLayerItem == nullptr )
		return false;
	auto begin = topLayerItem->subItems.begin( );
	auto end = topLayerItem->subItems.end( );
	for( ; begin != end; ++begin )
		if( *begin == this ) {
			topLayerItem->subItems.insert( ++begin, insert_item );
			emit topLayerItem->subItemChange( );
			return true;
		}
	return false;
}
bool NodeRunFunctionSequenceItem::insertFirst( NodeRunFunctionSequenceItem *insert_item ) {
	if( topLayerItem == nullptr )
		return false;
	topLayerItem->subItems.emplace_front( insert_item );
	emit topLayerItem->subItemChange( );
	return true;
}
bool NodeRunFunctionSequenceItem::insertEnd( NodeRunFunctionSequenceItem *insert_item ) {
	if( topLayerItem == nullptr )
		return false;
	topLayerItem->subItems.emplace_back( insert_item );
	emit topLayerItem->subItemChange( );
	return true;
}
bool NodeRunFunctionSequenceItem::replace( NodeRunFunctionSequenceItem *insert_item ) {
	if( topLayerItem == nullptr )
		return false;
	auto begin = topLayerItem->subItems.begin( );
	auto end = topLayerItem->subItems.end( );
	for( ; begin != end; ++begin )
		if( *begin == this ) {
			topLayerItem->subItems.insert( begin, insert_item );

			begin = topLayerItem->subItems.begin( );
			end = topLayerItem->subItems.end( );
			for( ; begin != end; ++begin )
				if( *begin == this ) {
					topLayerItem->subItems.erase( begin );
					break;
				}
			emit topLayerItem->subItemChange( );
			return true;
		}
	return false;
}
bool NodeRunFunctionSequenceItem::foreachSubLayerBeg( const foreachCallBack &foreach_call_brack ) {
	auto iterator = subItems.begin( );
	auto end = subItems.end( );
	foreach_call_brack( iterator, end );
	return true;

}
