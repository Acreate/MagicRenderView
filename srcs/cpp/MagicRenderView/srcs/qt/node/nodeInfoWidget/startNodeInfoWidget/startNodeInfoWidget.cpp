#include "startNodeInfoWidget.h"

#include <QFileDialog>
#include <QPushButton>
#include <qboxlayout.h>
void StartNodeInfoWidget::run( ) {
}
void StartNodeInfoWidget::builder( ) {
}
StartNodeInfoWidget::StartNodeInfoWidget( NodeItem *node_item ) : nodeItem( node_item ) {
	toolBtnVector = new QWidget( this );
	QHBoxLayout *qhBoxLayout = new QHBoxLayout( toolBtnVector );
	QPushButton *runBtn = new QPushButton( toolBtnVector );
	runBtn->setText( "运行" );
	connect( runBtn, &QPushButton::clicked, this, &StartNodeInfoWidget::run );
	qhBoxLayout->addWidget( runBtn );

	QPushButton *builderBtn = new QPushButton( toolBtnVector );
	builderBtn->setText( "编译" );
	connect( builderBtn, &QPushButton::clicked, this, &StartNodeInfoWidget::builder );
	qhBoxLayout->addWidget( builderBtn );
}
void StartNodeInfoWidget::toolWidgetMoveToMid( ) {
	int toolWidgetWidth = toolBtnVector->width( );
	int width = this->width( );
	int mid = width - toolWidgetWidth;
	mid /= 2;
	toolBtnVector->move( mid, 0 );
}
void StartNodeInfoWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	toolWidgetMoveToMid( );
}
void StartNodeInfoWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	toolWidgetMoveToMid( );
}
