#include "selectColorWidget.h"

SelectColorWidget::SelectColorWidget( QWidget *parnet ) {
}
void SelectColorWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void SelectColorWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}
void SelectColorWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
}
void SelectColorWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	// todo : 绘制颜色
}
