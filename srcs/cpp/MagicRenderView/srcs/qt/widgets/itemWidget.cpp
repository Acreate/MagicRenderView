#include "./itemWidget.h"

#include <QPainter>
ItemWidget::ItemWidget( QWidget *parent ) : QWidget( parent ) {
}
ItemWidget::~ItemWidget( ) {
	emit s_signals_deleteItemWidget( this );
}
void ItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::yellow );
}

void ItemWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	emit s_signals_clickItemWidget( this );
}
void ItemWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
	emit s_signals_doubleClickItemWidget( this );
}
