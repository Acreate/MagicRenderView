#include "./nodeRunFunctionSequenceItem.h"

#include "../widgets/NodeRunSequenceItemFunctionWidget.h"
#include "../widgets/NodeRunSequenceItemWidget.h"
#include "../widgets/nodeRunSequenceWidget.h"
NodeRunFunctionSequenceItem::NodeRunFunctionSequenceItem( NodeRunSequenceWidget *run_sequence_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, NodeRunFunctionSequenceItem *top_layer_item ) : topLayerItem( top_layer_item ), functionDeclaration( function_declaration ), runMainSequenceWidget( run_sequence_widget ) {
	if( functionDeclaration )
		renderCurrentNodeFunctionWidget = new NodeRunSequenceItemFunctionWidget( this );
	else
		renderCurrentNodeFunctionWidget = nullptr;
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
	if( renderCurrentNodeFunctionWidget )
		delete renderCurrentNodeFunctionWidget;
	for( auto &item : subItems ) {
		item->topLayerItem = nullptr;
		delete item;
	}
	if( renderCurrentNodeFunctionWidget )
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
			topLayerItem->subItems.insert( begin, insert_item );
			insert_item->topLayerItem = topLayerItem;
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
			insert_item->topLayerItem = topLayerItem;
			emit topLayerItem->subItemChange( );
			return true;
		}
	return false;
}
bool NodeRunFunctionSequenceItem::insertFirst( NodeRunFunctionSequenceItem *insert_item ) {
	if( topLayerItem == nullptr )
		return false;
	topLayerItem->subItems.emplace_front( insert_item );
	insert_item->topLayerItem = topLayerItem;
	emit topLayerItem->subItemChange( );
	return true;
}
bool NodeRunFunctionSequenceItem::insertEnd( NodeRunFunctionSequenceItem *insert_item ) {
	if( topLayerItem == nullptr )
		return false;
	topLayerItem->subItems.emplace_back( insert_item );
	insert_item->topLayerItem = topLayerItem;
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
			topLayerItem->subItems.erase( begin );
			insert_item->topLayerItem = topLayerItem;
			emit topLayerItem->subItemChange( );
			return true;
		}
	return false;
}
bool NodeRunFunctionSequenceItem::foreachSubLayerBeg( const foreachCallBack &foreach_call_brack ) {
	auto begin = subItems.begin( );
	auto end = subItems.end( );
	foreach_call_brack( begin, end );
	return true;

}
NodeRunFunctionSequenceItem * NodeRunFunctionSequenceItem::insertNodeRender( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point ) {
	if( renderSubItemsNodeWidget->isHidden( ) )
		return nullptr;
	auto contentsRect = renderSubItemsNodeWidget->contentsRect( );
	auto mapFromGlobal = renderSubItemsNodeWidget->mapFromGlobal( glob_point );
	auto begin = subItems.begin( );
	auto end = subItems.end( );
	if( contentsRect.contains( mapFromGlobal ) == true ) {
		auto newItem = new NodeRunFunctionSequenceItem( runMainSequenceWidget, function_declaration, this );
		int mapFromGlobalX = mapFromGlobal.x( );
		// 匹配当前序列窗口
		for( ; begin != end; ++begin )
			if( ( *begin )->renderCurrentNodeFunctionWidget->x( ) >= mapFromGlobalX )
				break;
		subItems.insert( begin, newItem );
		emit subItemChange( );
		return newItem;
	}

	// 子序列
	for( ; begin != end; ++begin ) {
		auto item = begin.operator*( )->insertNodeRender( generater_scripts_widget, function_declaration, glob_point, set_point );
		if( item != nullptr )
			return item;
	}
	return nullptr;
}
