#include "./NodeRunSequenceItemFunctionWidget.h"

#include <QPainter>

#include "NodeRunSequenceItemWidget.h"
#include "nodeRunSequenceWidget.h"
NodeRunSequenceItemFunctionWidget::NodeRunSequenceItemFunctionWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item ) : QWidget( node_run_function_sequence_item->runMainSequenceWidget ), nodeRunFunctionSequenceItem( node_run_function_sequence_item ) {
	setFixedSize( 100, 200 );
	connect( node_run_function_sequence_item, &NodeRunFunctionSequenceItem::showCurrentItemWidget, node_run_function_sequence_item->runMainSequenceWidget, &NodeRunSequenceWidget::itemThisWidgetShowEvent );
	connect( node_run_function_sequence_item, &NodeRunFunctionSequenceItem::currentItemDoubleClick, node_run_function_sequence_item->runMainSequenceWidget, &NodeRunSequenceWidget::itemThisWidgetCurrentItemDoubleClick );
}
void NodeRunSequenceItemFunctionWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );

	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkGreen );
}
void NodeRunSequenceItemFunctionWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
	emit nodeRunFunctionSequenceItem->currentItemDoubleClick( this, nodeRunFunctionSequenceItem );
}
void NodeRunSequenceItemFunctionWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	emit nodeRunFunctionSequenceItem->showCurrentItemWidget( this, true, nodeRunFunctionSequenceItem );
}
void NodeRunSequenceItemFunctionWidget::hideEvent( QHideEvent *event ) {
	QWidget::hideEvent( event );
	emit nodeRunFunctionSequenceItem->showCurrentItemWidget( this, false, nodeRunFunctionSequenceItem );
}
