#include "./mainWidget.h"

#include <QPainter>

#include "../../application/application.h"

#include "../scrollAreas/nodeListScrollAreasWidget.h"
#include "../scrollAreas/nodeRenderScrollAreasWidget.h"
#include "../scrollAreas/nodeScriptsScrollAreasWidget.h"

MainWidget::MainWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent, flags ) {
	this->appInstance = Application::getApplicationInstancePtr( );
	nodeListWidget = new NodeListScrollAreasWidget( this );
	nodeRenderWidget = new NodeRenderScrollAreasWidget( this );
	nodeScriptsWidget = new NodeScriptsScrollAreasWidget( this );
	
	renderLayout.first = "Application/MainWindow/MainWidget/NodeListScrollAreasWidget";
	renderLayout.second = 8;
	renderLayout.second = appInstance->value( renderLayout.first, renderLayout.second ).toLongLong( );

	nodeListLayout.first = "Application/MainWindow/MainWidget/NodeRenderScrollAreasWidget";
	nodeListLayout.second = 3;
	nodeListLayout.second = appInstance->value( nodeListLayout.first, nodeListLayout.second ).toLongLong( );

	nodeScriptsLayout.first = "Application/MainWindow/MainWidget/NodeScriptsScrollAreasWidget";
	nodeScriptsLayout.second = 3;
	nodeScriptsLayout.second = appInstance->value( nodeScriptsLayout.first, nodeScriptsLayout.second ).toLongLong( );
	
	nodeListWidget->show( );
	nodeRenderWidget->show( );
	nodeScriptsWidget->show( );
	
	updateResize( );
}
MainWidget::~MainWidget( ) {
	appInstance->setValue( renderLayout.first, renderLayout.second );
	appInstance->setValue( nodeListLayout.first, nodeListLayout.second );
	appInstance->setValue( nodeScriptsLayout.first, nodeScriptsLayout.second );
	appInstance->sync( );
}
void MainWidget::paintEvent( QPaintEvent *event ) {

	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::darkGreen );
}
void MainWidget::updateResize( ) {
	auto rect = contentsRect( );
	int currentWidth = rect.width( );
	int currentHeight = rect.height( );
	int mulBase = currentHeight / ( renderLayout.second + nodeListLayout.second + nodeScriptsLayout.second );
	int h = mulBase * renderLayout.second;

	nodeRenderWidget->move( 0, 0 );
	nodeRenderWidget->setFixedSize( currentWidth, h );

	nodeListWidget->move( 0, h );
	size_t h1 = mulBase * nodeListLayout.second;
	nodeListWidget->setFixedSize( currentWidth, h1 );
	h = h + h1;
	nodeScriptsWidget->move( 0, h );
	nodeScriptsWidget->setFixedSize( currentWidth, currentHeight - h );

}
void MainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateResize( );
}
