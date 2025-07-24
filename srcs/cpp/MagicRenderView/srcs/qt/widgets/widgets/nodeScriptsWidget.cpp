#include "./nodeScriptsWidget.h"

#include <QPainter>
NodeScriptsWidget::NodeScriptsWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent ) {
}
NodeScriptsWidget::~NodeScriptsWidget( ) {
}
void NodeScriptsWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::red );
}
