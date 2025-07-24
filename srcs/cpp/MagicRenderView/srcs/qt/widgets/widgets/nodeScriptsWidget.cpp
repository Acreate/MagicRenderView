#include "./nodeScriptsWidget.h"

#include <QPainter>
NodeScriptsWidget::NodeScriptsWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent ) {
}
NodeScriptsWidget::~NodeScriptsWidget( ) {
}
void NodeScriptsWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	auto rect = contentsRect( );
	painter.fillRect( rect, Qt::red );
	QPen pen( Qt::GlobalColor::black );
	int width = 4;
	pen.setWidth( width );
	painter.setPen( pen );
	painter.setBrush( QColor( 0, 0, 0, 0 ) );
	auto size = rect.size( );
	painter.drawRect( width, width, size.width( ) - width * 2 - 1, size.height( ) - width * 2 - 1 );
}
