#include "./mainWidget.h"

#include <QPainter>

#include "../scrollAreas/nodeListScrollAreasWidget.h"
#include "../scrollAreas/nodeRenderScrollAreasWidget.h"
#include "../scrollAreas/nodeScriptsScrollAreasWidget.h"

MainWidget::MainWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent, flags ) {
	nodeListWidget = new NodeListScrollAreasWidget( this );
	nodeRenderWidget = new NodeRenderScrollAreasWidget( this );
	nodeScriptsWidget = new NodeScriptsScrollAreasWidget( this );
	updateResize( );
	nodeListWidget->show( );
	nodeRenderWidget->show( );
	nodeScriptsWidget->show( );
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
	int mulBase = currentHeight / 10;
	int h = mulBase * 8;

	nodeRenderWidget->move( 0, 0 );
	nodeRenderWidget->setFixedSize( currentWidth, h );

	nodeListWidget->move( 0, h );
	nodeListWidget->setFixedSize( currentWidth, mulBase );

	nodeScriptsWidget->move( 0, h + mulBase );
	nodeScriptsWidget->setFixedSize( currentWidth, currentHeight - mulBase - h );

}
void MainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateResize( );
}
