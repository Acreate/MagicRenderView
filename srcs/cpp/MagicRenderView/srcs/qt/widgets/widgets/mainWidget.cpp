#include "./mainWidget.h"

#include <QPainter>

#include "../../application/application.h"

#include "../../status/widgetStatus.h"

#include "../scrollAreas/nodeListScrollAreasWidget.h"
#include "../scrollAreas/nodeRenderScrollAreasWidget.h"
#include "../scrollAreas/nodeScriptsScrollAreasWidget.h"

MainWidget::MainWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent, flags ) {
	this->appInstance = Application::getApplicationInstancePtr( );
	nodeListWidget = new NodeListScrollAreasWidget( this );
	nodeRenderWidget = new NodeRenderScrollAreasWidget( this );
	nodeScriptsWidget = new NodeScriptsScrollAreasWidget( this );

	nodeRenderStatus = new WidgetStatus( "Application/////MainWindow/MainWidget/NodeRenderScrollAreasWidget/////", nodeRenderWidget, 8, true );
	nodeListStatus = new WidgetStatus( "Application/MainWindow/MainWidget/NodeListScrollAreasWidget", nodeRenderWidget, 3, true );
	nodeScriptsSatatus = new WidgetStatus( "Application/MainWindow/MainWidget/NodeScriptsScrollAreasWidget", nodeRenderWidget, 3, true );

	nodeRenderStatus->getAppIniValue( );
	nodeListStatus->getAppIniValue( );
	nodeScriptsSatatus->getAppIniValue( );

	if( nodeListStatus->isShow( ) )
		nodeListWidget->show( );
	if( nodeRenderStatus->isShow( ) )
		nodeRenderWidget->show( );
	if( nodeScriptsSatatus->isShow( ) )
		nodeScriptsWidget->show( );

	updateResize( );
}
MainWidget::~MainWidget( ) {
	nodeRenderStatus->setAppIniValue( );
	nodeListStatus->setAppIniValue( );
	nodeScriptsSatatus->setAppIniValue( );
	appInstance->syncAppValueIniFile( );
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
	size_t mulBase;
	size_t nodeListWidgetHeight = nodeListStatus->getLayout( );
	size_t nodeScriptsWidgetHeight = nodeScriptsSatatus->getLayout( );
	size_t nodeRenderWidgetHeight = nodeRenderStatus->getLayout( );

	if( nodeRenderWidget->isHidden( ) )
		nodeRenderWidgetHeight = 0;

	if( nodeListWidget->isHidden( ) )
		nodeListWidgetHeight = 0;

	if( nodeScriptsWidget->isHidden( ) )
		nodeScriptsWidgetHeight = 0;

	size_t mup = nodeRenderWidgetHeight + nodeListWidgetHeight + nodeScriptsWidgetHeight;
	if( mup == 0 )
		return; // 没有显示的内容
	mulBase = currentHeight / mup;
	nodeListWidgetHeight = mulBase * nodeListWidgetHeight;
	nodeScriptsWidgetHeight = mulBase * nodeScriptsWidgetHeight;
	nodeRenderWidgetHeight = currentHeight - nodeListWidgetHeight - nodeScriptsWidgetHeight;

	nodeListWidget->setFixedSize( currentWidth, nodeListWidgetHeight );
	nodeScriptsWidget->setFixedSize( currentWidth, nodeScriptsWidgetHeight );
	nodeRenderWidget->setFixedSize( currentWidth, nodeRenderWidgetHeight );

	nodeRenderWidget->move( 0, 0 );
	nodeListWidget->move( 0, nodeRenderWidgetHeight );
	nodeScriptsWidget->move( 0, nodeRenderWidgetHeight + nodeListWidgetHeight );

}
void MainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateResize( );
}
