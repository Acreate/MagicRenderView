#include "./protInputItemWidget.h"

#include <QPainter>
ProtInputItemWidget::ProtInputItemWidget( QWidget *parent ) : QWidget( parent ) {
	setFixedSize( 200, 50 );
}
void ProtInputItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), QColorConstants::DarkYellow );
}
