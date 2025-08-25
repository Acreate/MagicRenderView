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
	QPainter painter( this );
	auto pen = painter.pen( );
	int width = 5;
	int widthEnd = 5 * 2;
	pen.setWidth( width );
	painter.setPen( pen );
	auto size = contentsRect( ).size( );
	auto rect = QRect( width, width, size.width( ) - widthEnd, size.height( ) - widthEnd );

	painter.drawRect( rect );
	auto image = functionDeclaration->getImage( );
	if( image == nullptr )
		return;
	painter.drawImage( rect, *image );
}
void NodeFuncPreviewImageWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	repaint( );
}
