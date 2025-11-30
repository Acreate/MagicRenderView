#include "mainWidget.h"
#include <QResizeEvent>

#include "drawLinkWidget.h"
#include "drawNodeWidget.h"
#include "mainWidgetScrollArea.h"

#include "../app/application.h"

#include "../node/node/node.h"

MainWidget::MainWidget( MainWidgetScrollArea *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), mainWidgetScrollArea( parent ), drawLinkWidget( nullptr ), drawNodeWidget( nullptr ) {

}
bool MainWidget::ensureVisible( Node *target ) {
	if( target->parent( ) != drawNodeWidget )
		return false;
	auto point = target->pos( );
	QSize renderSize = target->size( );
	int w = renderSize.width( ) + point.x( );
	int h = renderSize.height( ) + point.y( );
	renderSize = size( );
	int oldW = renderSize.width( );
	int oldH = renderSize.height( );
	if( oldW > w )
		w = oldW;
	if( oldH > h )
		h = oldH;
	if( oldW == w && oldH == h )
		return true;
	setMinimumSize( w, h );
	mainWidgetScrollArea->ensureVisible( w, h );
	return true;
}
bool MainWidget::init( ) {
	if( drawLinkWidget )
		delete drawLinkWidget;
	if( drawNodeWidget )
		delete drawNodeWidget;
	drawLinkWidget = new DrawLinkWidget( this );
	drawNodeWidget = new DrawNodeWidget( this );
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
	return true;
}
void MainWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	auto newSize = event->size( );
	drawNodeWidget->resize( newSize );
	drawLinkWidget->resize( newSize );
	drawNodeWidget->raise( );
	drawLinkWidget->raise( );
}
