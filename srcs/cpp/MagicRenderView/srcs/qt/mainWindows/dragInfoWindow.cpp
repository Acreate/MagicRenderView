#include "./dragInfoWindow.h"

#include <QLabel>
#include <qgridlayout.h>

#include "widgets/mainWidget/nodeListScrollAreasWidget/nodeListWidget/nodeGeneraterListWidget/nodePreviewScrollAreasWidget/NodePreviewWidget/nodeFuncPreviewImageWidget.h"

DragInfoWindow::DragInfoWindow( ) {
	draw = new QLabel( this );
	draw->setFixedSize( 100, 200 );
	draw->move( 0, 0 );
	setContentsMargins( 0, 0, 0, 0 );
	hide( );
	auto oldLayout = layout( );
	if( oldLayout )
		delete oldLayout;
	oldLayout = new QVBoxLayout( this );
	oldLayout->setContentsMargins( 0, 0, 0, 0 );
	oldLayout->addWidget( draw );
	isShowInfo = false;
	this->setWindowFlags( Qt::FramelessWindowHint );
}
void DragInfoWindow::setDragFunctionPreviewWidget( const NodeFuncPreviewImageWidget *drag_function_preview_widget ) {
	QImage renderImage = drag_function_preview_widget->getRenderImage( );
	QPixmap fromImage = QPixmap::fromImage( renderImage );
	draw->setPixmap( fromImage );
	isShowInfo = true;
}
void DragInfoWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
}
void DragInfoWindow::hideEvent( QHideEvent *event ) {
	QMainWindow::hideEvent( event );
	isShowInfo = false;
}
