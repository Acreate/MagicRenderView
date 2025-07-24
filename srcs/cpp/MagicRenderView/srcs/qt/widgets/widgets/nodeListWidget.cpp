#include "./nodeListWidget.h"

#include <QPainter>
NodeListWidget::NodeListWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent ) {

}
NodeListWidget::~NodeListWidget( ) {
}
void NodeListWidget::paintEvent( QPaintEvent *event ) {

	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::blue );
}
