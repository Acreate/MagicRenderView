#include "runNodeModuleItemWidget.h"

#include <QPainter>

#include "../../../application/application.h"

#include "../../item/nodeItem.h"
RunNodeModuleItemWidget::RunNodeModuleItemWidget( NodeItem *node_item_ptr, QWidget *parent, const Qt::WindowFlags &f ) : QLabel( "", parent, f ), nodeItemPtr( node_item_ptr ) {

	penWidth = 2;
	doublePenWidth = penWidth * 2;
	titile = QString( "%1->%2" ).arg( nodeItemPtr->getMetaObjectPathName( ) ).arg( nodeItemPtr->getGenerateCode( ) );
	setTitile( titile );
}
void RunNodeModuleItemWidget::setTitile( const QString &titile ) {
	
	this->titile = titile;
	auto applicationInstancePtr = Application::getApplicationInstancePtr( );
	auto font = applicationInstancePtr->getFont( );

	QFontMetrics fontMetrics( font );
	auto boundingRect = fontMetrics.boundingRect( titile );

	auto titleWidth = boundingRect.width( ) + boundingRect.x( );
	auto titleHeight = fontMetrics.height( );

	QSize newSize( titleWidth + doublePenWidth, titleHeight + doublePenWidth );
	titleBuff = QImage( newSize, QImage::Format_RGBA8888 );

	titleBuff.fill( 0 );
	QPainter painter( &titleBuff );

	QRect rect { penWidth, penWidth, titleWidth, titleHeight };
	auto oldPen = painter.pen( );

	auto pen = oldPen;
	pen.setWidth( penWidth );
	pen.setColor( Qt::GlobalColor::red );
	painter.setPen( pen );
	painter.drawRect( rect );

	painter.setPen( oldPen );
	painter.setFont( font );
	int leading = fontMetrics.leading( );
	int descent = fontMetrics.descent( );
	int y = titleHeight - leading - descent ;
	painter.drawText( 0, y, titile );
	painter.end( );
	setMinimumSize( newSize );
}
void RunNodeModuleItemWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QLabel::mouseDoubleClickEvent( event );
	if( nodeItemPtr == nullptr )
		return;
	auto itemWidget = nodeItemPtr->getNodeItemWidget( );
	if( itemWidget == nullptr )
		return;
	itemWidget->show( );
	itemWidget->raise( );
}
void RunNodeModuleItemWidget::paintEvent( QPaintEvent *paint_event ) {
	QLabel::paintEvent( paint_event );
	QPainter painter( this );
	painter.drawImage( 0, 0, titleBuff );
}
