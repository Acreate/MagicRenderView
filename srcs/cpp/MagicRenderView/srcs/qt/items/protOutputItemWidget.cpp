#include "./protOutputItemWidget.h"

#include <QPainter>
ProtOutputItemWidget::ProtOutputItemWidget( QWidget *parent ) : QWidget( parent ) {
	setFixedSize( 200, 50 );
}
void ProtOutputItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), QColorConstants::DarkRed );
}
