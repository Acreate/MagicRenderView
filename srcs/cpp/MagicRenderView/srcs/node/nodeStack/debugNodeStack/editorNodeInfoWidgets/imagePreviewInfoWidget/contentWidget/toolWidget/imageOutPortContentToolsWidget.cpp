#include "imageOutPortContentToolsWidget.h"

#include <app/application.h>
#include <director/builderDirector.h>
#include <node/node/node.h>
#include <qpushbutton.h>
#include <QVBoxLayout>
void ImageOutPortContentToolsWidget::RunBtnClick( ) {
	if( targetNode )
		emit click_builder_target_signal( targetNode );
}
void ImageOutPortContentToolsWidget::createNodeRunInfoBtnClickInfoAction( ) {
	auto nodeRunInfo = builderDirector->getNodeRunInfo( );
	if( targetNode && nodeRunInfo != nullptr ) {
		runBtn->setText( tr( "运行到 [%1]" ).arg( targetNode->toQString( ) ) );
		setEnabled( true );
	} else {
		runBtn->setText( tr( "未匹配" ) );
		setEnabled( false );
	}
}
void ImageOutPortContentToolsWidget::releaseNodeRunInfoBtnClickInfoAction( ) {
	runBtn->setText( tr( "未匹配" ) );
	setEnabled( false );
}
void ImageOutPortContentToolsWidget::setTargetNode( Node *target_node ) {
	targetNode = target_node;
	auto nodeRunInfo = builderDirector->getNodeRunInfo( );
	if( target_node && nodeRunInfo != nullptr ) {
		runBtn->setText( tr( "运行到 [%1]" ).arg( target_node->toQString( ) ) );
		setEnabled( true );
	} else {
		runBtn->setText( tr( "未匹配" ) );
		setEnabled( false );
	}
}
ImageOutPortContentToolsWidget::ImageOutPortContentToolsWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	builderDirector = Application::getInstancePtr( )->getBuilderDirector( );
	targetNode = nullptr;
	auto layout1 = layout( );
	if( layout1 )
		delete layout1;
	mainLayout = new QVBoxLayout( this );
	runBtn = new QPushButton( tr( "未匹配" ), this );
	setEnabled( false );
	mainLayout->addWidget( runBtn );
	connect( runBtn, &QPushButton::clicked, this, &ImageOutPortContentToolsWidget::RunBtnClick );
	connect( builderDirector, &BuilderDirector::create_node_run_info_signalr, this, &ImageOutPortContentToolsWidget::createNodeRunInfoBtnClickInfoAction );
	connect( builderDirector, &BuilderDirector::release_node_run_info_signal, this, &ImageOutPortContentToolsWidget::releaseNodeRunInfoBtnClickInfoAction );
}
