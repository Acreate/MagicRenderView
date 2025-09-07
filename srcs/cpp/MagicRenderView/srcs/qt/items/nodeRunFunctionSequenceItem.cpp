#include "./nodeRunFunctionSequenceItem.h"

#include "../widgets/NodeRunFunctionSequenceItemRnderWidget.h"
#include "../widgets/nodeRunSequenceWidget.h"
NodeRunFunctionSequenceItem::NodeRunFunctionSequenceItem( NodeRunSequenceWidget *run_sequence_widget, NodeRunFunctionSequenceItem *top_layer_item ) : runSequenceWidget( run_sequence_widget ), topLayerItem( top_layer_item ) {
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
		emit topLayerItem->itemChange( );
		topLayerItem = nullptr;
	}
	for( auto &item : subItems ) {
		item->topLayerItem = nullptr;
		delete item;
	}
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
			emit topLayerItem->itemChange( );
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
			emit topLayerItem->itemChange( );
			return true;
		}
	return false;
}
bool NodeRunFunctionSequenceItem::insertFirst( NodeRunFunctionSequenceItem *insert_item ) {
	if( topLayerItem == nullptr )
		return false;
	topLayerItem->subItems.emplace_front( insert_item );
	emit topLayerItem->itemChange( );
	return true;
}
bool NodeRunFunctionSequenceItem::insertEnd( NodeRunFunctionSequenceItem *insert_item ) {
	if( topLayerItem == nullptr )
		return false;
	topLayerItem->subItems.emplace_back( insert_item );
	emit topLayerItem->itemChange( );
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
			emit topLayerItem->itemChange( );
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
NodeRunFunctionSequenceItem * NodeRunFunctionSequenceItem::setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point ) {
	if( renderWidget->isHidden( ) )
		return nullptr;
	auto mapFromGlobal = renderWidget->mapFromGlobal( glob_point );
	QRect contentsRect = renderWidget->contentsRect( );
	NodeRunFunctionSequenceItem *functionSequenceItem = nullptr;
	for( auto &item : subItems ) {
		functionSequenceItem = item->setRunFunctionWidget( generater_scripts_widget, function_declaration, glob_point, set_point );
		if( functionSequenceItem )
			return functionSequenceItem;
	}
	if( contentsRect.contains( mapFromGlobal ) ) {
		functionSequenceItem = renderWidget->setRunFunctionWidget( generater_scripts_widget, function_declaration, glob_point, mapFromGlobal );
		if( functionSequenceItem )
			return functionSequenceItem;
	}

	return functionSequenceItem;
}
