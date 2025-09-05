#include "./nodeRenderWidget.h"

#include <QPainter>

NodeRenderWidget::NodeRenderWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
}
NodeRenderWidget::~NodeRenderWidget( ) {
}
void NodeRenderWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	auto rect = contentsRect( );
	painter.fillRect( contentsRect( ), { 255, 128, 0 } );
	QPen pen( Qt::GlobalColor::black );
	int width = 4;
	pen.setWidth( width );
	painter.setPen( pen );
	painter.setBrush( QColor( 0, 0, 0, 0 ) );
	auto size = rect.size( );
	painter.drawRect( width, width, size.width( ) - width * 2 - 1, size.height( ) - width * 2 - 1 );
}
void NodeRenderWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
