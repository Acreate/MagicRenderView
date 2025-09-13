#include "./NodeRunSequenceItemWidget.h"

#include <QPainter>
#include <qevent.h>

#include "NodeRunSequenceItemFunctionWidget.h"
#include "nodeRunSequenceWidget.h"

#include "../items/nodeRunFunctionSequenceItem.h"
NodeRunSequenceItemWidget::NodeRunSequenceItemWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item ) : QWidget( node_run_function_sequence_item->runMainSequenceWidget ), nodeRunFunctionSequenceItem( node_run_function_sequence_item ) {
	connect( node_run_function_sequence_item, &NodeRunFunctionSequenceItem::showSubItemWidget, node_run_function_sequence_item->runMainSequenceWidget, &NodeRunSequenceWidget::itemSubWidgetShowEvent );
}
void NodeRunSequenceItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkBlue );

}
void NodeRunSequenceItemWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	emit nodeRunFunctionSequenceItem->showSubItemWidget( this, true, nodeRunFunctionSequenceItem );
}
void NodeRunSequenceItemWidget::hideEvent( QHideEvent *event ) {
	QWidget::hideEvent( event );
	emit nodeRunFunctionSequenceItem->showSubItemWidget( this, false, nodeRunFunctionSequenceItem );
}
