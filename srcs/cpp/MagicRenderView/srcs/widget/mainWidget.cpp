#include "mainWidget.h"
#include <QResizeEvent>

#include "drawLinkWidget.h"
#include "drawNodeWidget.h"

#include "../app/application.h"

MainWidget::MainWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), drawLinkWidget( nullptr ), drawNodeWidget( nullptr ) {

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
