#include "./nodeRenderWidget.h"

#include <QPainter>

NodeRenderWidget::~NodeRenderWidget( ) {
}
void NodeRenderWidget::paintEvent( QPaintEvent *event ) {
	QScrollArea::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::red );
}
