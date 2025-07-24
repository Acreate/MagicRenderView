#include "./nodeRenderWidget.h"

#include <QPainter>

NodeRenderWidget::NodeRenderWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent ) {
}
NodeRenderWidget::~NodeRenderWidget( ) {
}
void NodeRenderWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), { 255, 128, 0 } );
}
