#include "mainWidget.h"

#include <QMenu>
#include <QResizeEvent>

#include "drawLinkWidget.h"
#include "drawNodeWidget.h"
#include "mainWidgetScrollArea.h"

#include "../app/application.h"

#include "../director/nodeDirector.h"

#include "../node/node/node.h"

#include "../win/mainWindow.h"

MainWidget::MainWidget( MainWidgetScrollArea *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), mainWidgetScrollArea( parent ), drawLinkWidget( nullptr ), drawNodeWidget( nullptr ), clickInfoPtr( nullptr ) {

}
MainWidget::~MainWidget( ) {
	if( drawLinkWidget )
		delete drawLinkWidget;
	if( drawNodeWidget )
		delete drawNodeWidget;
	if( clickInfoPtr )
		delete clickInfoPtr;
}
bool MainWidget::ensureVisible( Node *target ) {
	if( target->parent( ) != drawNodeWidget )
		return false;
	auto point = target->pos( );
	auto toGlobal = drawNodeWidget->mapToGlobal( point );
	auto fromGlobal = mainWindow->mapFromGlobal( toGlobal );
	int fromGlobalX = fromGlobal.x( );
	int fromGlobalY = fromGlobal.y( );
	QSize renderSize = target->size( );
	if( fromGlobalX < 0 || fromGlobalY < 0 ) {
		mainWidgetScrollArea->ensureVisible( point.x( ), point.y( ) );
		return true;
	}
	fromGlobalX = renderSize.width( ) + point.x( );
	fromGlobalY = renderSize.height( ) + point.y( );
	renderSize = minimumSize( );
	int oldW = renderSize.width( );
	int oldH = renderSize.height( );
	if( oldW > fromGlobalX )
		fromGlobalX = oldW;
	if( oldH > fromGlobalY )
		fromGlobalY = oldH;
	if( oldW == fromGlobalX && oldH == fromGlobalY )
		return true;
	setMinimumSize( fromGlobalX, fromGlobalY );
	mainWidgetScrollArea->ensureVisible( fromGlobalX, fromGlobalY );
	return true;
}
bool MainWidget::init( ) {
	if( drawLinkWidget )
		delete drawLinkWidget;
	if( drawNodeWidget )
		delete drawNodeWidget;
	if( clickInfoPtr )
		delete clickInfoPtr;
	clickInfoPtr = new NodeClickInfo( NodeEnum::NodeClickType::None, nullptr, nullptr, nullptr );
	drawLinkWidget = new DrawLinkWidget( this );
	drawNodeWidget = new DrawNodeWidget( this );
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
	mainWindow = appInstancePtr->getMainWindow( );
	nodeCreateMenu = nodeDirector->getNodeCreateMenu( );
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
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );

}
void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );

	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			if( drawNodeWidget->getPointNodeClickInfo( event->pos( ), *clickInfoPtr ) ) {
				ensureVisible( clickInfoPtr->getClickNode( ) );
			}
			break;
		case Qt::RightButton :
			drawNodeWidget->menuPopPoint = mapToGlobal( event->pos( ) );
			nodeCreateMenu->popup( drawNodeWidget->menuPopPoint );
			break;
		case Qt::MiddleButton :
			break;
	}
}
