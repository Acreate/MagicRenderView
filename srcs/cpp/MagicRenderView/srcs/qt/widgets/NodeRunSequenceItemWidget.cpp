#include "./NodeRunSequenceItemWidget.h"

#include <QPainter>

#include "NodeRunSequenceItemFunctionWidget.h"
#include "nodeRunSequenceWidget.h"

#include "../items/nodeRunFunctionSequenceItem.h"
NodeRunSequenceItemWidget::NodeRunSequenceItemWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item ) : QWidget( node_run_function_sequence_item->runMainSequenceWidget ), nodeRunFunctionSequenceItem( node_run_function_sequence_item ) {
	minWidth = 100;
	minHeight = 200;
	connect( node_run_function_sequence_item, &NodeRunFunctionSequenceItem::subItemChange, this, &NodeRunSequenceItemWidget::updateRenderItems );
}
void NodeRunSequenceItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkBlue );

}
void NodeRunSequenceItemWidget::updateRenderItems( ) {
	auto iterator = nodeRunFunctionSequenceItem->subItems.begin( );
	auto end = nodeRunFunctionSequenceItem->subItems.end( );
	int itemWidgetSpace = 10;
	int x = itemWidgetSpace;
	int y = 5;
	int height = 0;
	for( ; iterator != end; ++iterator ) {
		auto functionWidget = iterator.operator*( )->renderCurrentNodeFunctionWidget;
		if( functionWidget == nullptr )
			continue;
		functionWidget->setParent( nodeRunFunctionSequenceItem->renderSubItemsNodeWidget );
		functionWidget->show( );
		functionWidget->move( x, y );
		x += functionWidget->width( ) + itemWidgetSpace;
		int widgetHeith = functionWidget->height( );
		if( widgetHeith > height )
			height = widgetHeith;
	}
	if( x < minWidth )
		x = minWidth;
	if( height < minHeight )
		height = minHeight;
	minWidth = x;
	minHeight = height;
	emit sequenceItemUpdate( this );
}
