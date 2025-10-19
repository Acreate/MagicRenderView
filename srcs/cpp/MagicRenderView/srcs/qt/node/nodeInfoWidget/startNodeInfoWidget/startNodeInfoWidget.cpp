#include "startNodeInfoWidget.h"

#include <QFileDialog>
#include <QPushButton>
#include <qboxlayout.h>

#include "../../../application/application.h"

#include "../../director/nodeDirector.h"
void StartNodeInfoWidget::run( ) {
}
void StartNodeInfoWidget::builder( ) {
	if( nodeItemInfo == nullptr )
		runBtn->setEnabled( false );
	else
		runBtn->setEnabled( true );
}
void StartNodeInfoWidget::updateNodeItemInfoBuilderVector( NodeItemInfo *node_item_info ) {

	if( nodeItemInfo == nullptr ) {
		builderVector.clear( );
		if( nodeDirector->getNodeItemInfo( nodeItem, nodeItemInfo ) == false ) {
			builder( );
			return;
		}
	}

	size_t count = builderVector.size( );
	if( count == 0 ) {
		builder( );
		return;
	}
	auto data = builderVector.data( );
}
StartNodeInfoWidget::StartNodeInfoWidget( NodeItem *node_item ) : nodeItem( node_item ) {
	toolBtnVector = new QWidget( this );
	QHBoxLayout *qhBoxLayout = new QHBoxLayout( toolBtnVector );

	runBtn = new QPushButton( toolBtnVector );
	runBtn->setText( "运行" );
	connect( runBtn, &QPushButton::clicked, this, &StartNodeInfoWidget::run );
	runBtn->setEnabled( false );
	qhBoxLayout->addWidget( runBtn );

	builderBtn = new QPushButton( toolBtnVector );
	builderBtn->setText( "编译" );
	connect( builderBtn, &QPushButton::clicked, this, &StartNodeInfoWidget::builder );
	qhBoxLayout->addWidget( builderBtn );

	application = Application::getApplicationInstancePtr( );
	nodeDirector = application->getNodeDirector( );
	varGenerate = application->getVarGenerate( );
	nodeItemInfo = nullptr;
	connect( nodeDirector, &NodeDirector::nodeItemInfoRefChange, this, &StartNodeInfoWidget::updateNodeItemInfoBuilderVector );
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
