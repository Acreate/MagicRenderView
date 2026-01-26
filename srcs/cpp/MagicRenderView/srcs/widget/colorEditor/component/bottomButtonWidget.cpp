#include "bottomButtonWidget.h"
BottomButtonWidget::BottomButtonWidget( QWidget *parent ): QWidget( parent ) { }
void BottomButtonWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}
void BottomButtonWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
}
