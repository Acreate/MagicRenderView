#include "./dragInfoWindow.h"

#include <QLabel>
#include <qgridlayout.h>

#include "widgets/mainWidget/nodeListScrollAreasWidget/nodeListWidget/nodeGeneraterListWidget/nodePreviewScrollAreasWidget/NodePreviewWidget/nodeFuncPreviewImageWidget.h"

DragInfoWindow::DragInfoWindow( ) : QMainWindow( nullptr, Qt::FramelessWindowHint ) {
	setAttribute( Qt::WA_TranslucentBackground );
	draw = new QLabel( this );
	draw->setFixedSize( 100, 200 );
	draw->move( 0, 0 );
	draw->setAttribute( Qt::WA_TranslucentBackground );
	setContentsMargins( 0, 0, 0, 0 );
	hide( );
	auto oldLayout = layout( );
	if( oldLayout )
		delete oldLayout;
	oldLayout = new QVBoxLayout( this );
	oldLayout->setContentsMargins( 0, 0, 0, 0 );
	oldLayout->addWidget( draw );
	isShowInfo = false;
}
void DragInfoWindow::setDragFunctionPreviewWidget( const NodeFuncPreviewImageWidget *drag_function_preview_widget ) {
	QImage renderImage = drag_function_preview_widget->getRenderImage( );
	QPixmap fromImage = QPixmap::fromImage( renderImage );
	draw->setPixmap( fromImage );
	move( QCursor::pos( ) );
	isShowInfo = true;
	setWindowOpacity( 0.8 );
	show( );
}
void DragInfoWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
}
void DragInfoWindow::hideEvent( QHideEvent *event ) {
	QMainWindow::hideEvent( event );
	isShowInfo = false;
}
