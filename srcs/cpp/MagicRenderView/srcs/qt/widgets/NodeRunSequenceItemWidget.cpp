#include "./NodeRunSequenceItemWidget.h"

#include <QPainter>

#include "nodeRunSequenceWidget.h"

#include "../items/nodeRunFunctionSequenceItem.h"
NodeRunSequenceItemWidget::NodeRunSequenceItemWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item ) : QWidget( node_run_function_sequence_item->runMainSequenceWidget ), nodeRunSequenceWidget( node_run_function_sequence_item->runMainSequenceWidget ) {
}
void NodeRunSequenceItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter(this);
	painter.fillRect( contentsRect(  ), Qt::GlobalColor::darkBlue );
	
}
