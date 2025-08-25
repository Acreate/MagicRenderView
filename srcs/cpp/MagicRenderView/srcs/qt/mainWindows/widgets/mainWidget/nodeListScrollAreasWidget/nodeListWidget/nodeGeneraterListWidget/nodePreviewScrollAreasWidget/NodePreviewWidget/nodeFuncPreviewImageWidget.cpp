#include "./nodeFuncPreviewImageWidget.h"

#include <QPainter>
#include <qboxlayout.h>

#include <qt/functionDeclaration/IFunctionDeclaration.h>

NodeFuncPreviewImageWidget::NodeFuncPreviewImageWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
}
bool NodeFuncPreviewImageWidget::setFunctionDeclaration( const std_shared_ptr< IFunctionDeclaration > &function_declaration ) {
	functionDeclaration = function_declaration;
	return true;
}
void NodeFuncPreviewImageWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
}
void NodeFuncPreviewImageWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QRect widgetRect = contentsRect( );
	auto size = widgetRect.size( );
	renderImage = QImage( size, QImage::Format_RGBA8888 );
	renderImage.fill( 0 );
	QPainter painter( &renderImage );
	auto pen = painter.pen( );
	int width = 5;
	int widthEnd = 5 * 2;
	pen.setWidth( width );
	painter.setPen( pen );
	auto rect = QRect( width, width, size.width( ) - widthEnd, size.height( ) - widthEnd );

	painter.drawRect( rect );
	auto image = functionDeclaration->getImage( );
	if( image == nullptr )
		return;
	painter.drawImage( rect, *image );

	QPainter widgetPainter( this );
	widgetPainter.drawImage( widgetRect, renderImage );
}
void NodeFuncPreviewImageWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	repaint( );
}
