#include "colorEditor.h"

#include <QHBoxLayout>
#include <qpushbutton.h>
void ColorEditor::affirmBtenClick( ) {
	
}
void ColorEditor::cancelBtenClick( ) {
}
ColorEditor::ColorEditor( QWidget *parent ): QWidget( parent ) {
	auto mainLayout = new QHBoxLayout;
	affirmBtn = new QPushButton(tr( "确定" ), this);
	cancelBen = new QPushButton(tr( "取消" ), this);
	mainLayout->addWidget( affirmBtn );
	mainLayout->addWidget( cancelBen );
}
void ColorEditor::hideEvent( QHideEvent *event ) {
	QWidget::hideEvent( event );
}
void ColorEditor::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	// 当前 color 属性显示
}
