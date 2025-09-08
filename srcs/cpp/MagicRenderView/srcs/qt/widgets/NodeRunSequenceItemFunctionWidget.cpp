#include "./NodeRunSequenceItemFunctionWidget.h"

#include <QPainter>

#include "nodeRunSequenceWidget.h"
NodeRunSequenceItemFunctionWidget::NodeRunSequenceItemFunctionWidget( NodeRunFunctionSequenceItem *node_run_function_sequence_item ) : QWidget( node_run_function_sequence_item->runMainSequenceWidget ), nodeRunFunctionSequenceItem( node_run_function_sequence_item ) {
	setFixedSize( 100, 200 );
}
void NodeRunSequenceItemFunctionWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );

	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkGreen );
}
