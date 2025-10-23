#include "mainScrollAreaWidget.h"

#include <QMouseEvent>
#include <QScrollBar>

#include "mainWidget.h"

#include <qt/windows/mainWindow.h>

MainScrollAreaWidget::MainScrollAreaWidget( MainWindow *main_window ) : QScrollArea( main_window ), mainWidget( nullptr ) {
	isMidMouse = 0;
}
bool MainScrollAreaWidget::copyNodeItemActionInfo( ) {
	return mainWidget->copyNodeItemActionInfo( );
}
bool MainScrollAreaWidget::pasteNodeItemActionInfo( ) {
	return mainWidget->pasteNodeItemActionInfo( );
}
void MainScrollAreaWidget::mouseMoveEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mouseMoveEvent( mouse_event );
	if( isMidMouse == 1 ) {
		auto mouseMovePoint = mouse_event->pos( );
		auto point = fromGlobalPressPoint - mouseMovePoint;
		auto currentVerticalScrollBar = verticalScrollBar( );
		auto currentHorizontalScrollBar = horizontalScrollBar( );
		int x = point.x( );
		if( x > 0 )
			currentHorizontalScrollBar->setValue( currentHorizontalScrollBar->value( ) + 1 );
		else if( x < 0 )
			currentHorizontalScrollBar->setValue( currentHorizontalScrollBar->value( ) - 1 );

		int y = point.y( );
		if( y > 0 )
			currentVerticalScrollBar->setValue( currentVerticalScrollBar->value( ) + 1 );
		else if( y < 0 )
			currentVerticalScrollBar->setValue( currentVerticalScrollBar->value( ) - 1 );

		fromGlobalPressPoint = mouseMovePoint;
		x = mouseMovePoint.x( );
		auto widgetWidth = width( );
		if( x < 0 )
			mouseMovePoint.setX( widgetWidth );
		else if( x > widgetWidth )
			mouseMovePoint.setX( 0 );
		y = mouseMovePoint.y( );
		auto widgetHeight = height( );
		if( y < 0 )
			mouseMovePoint.setY( widgetHeight );
		else if( y > widgetHeight )
			mouseMovePoint.setY( 0 );
		if( fromGlobalPressPoint != mouseMovePoint ) {
			auto toGlobal = mapToGlobal( mouseMovePoint );
			QCursor::setPos( toGlobal );
			isMidMouse = 2;
		}
	} else if( isMidMouse == 2 ) {
		isMidMouse = 1;
		fromGlobalPressPoint = mouse_event->pos( );
	}
}
void MainScrollAreaWidget::mousePressEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mousePressEvent( mouse_event );
	Qt::MouseButton mouseButton = mouse_event->button( );
	switch( mouseButton ) {
		case Qt::MiddleButton :
			isMidMouse = 1;
			break;
	}
}
void MainScrollAreaWidget::mouseReleaseEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mouseReleaseEvent( mouse_event );
	isMidMouse = 0;
}
