#include "./nodeGeneraterItem.h"

#include <QPainter>

#include "../widgets/nodeGeneraterListWidget.h"

NodeGeneraterItem::NodeGeneraterItem( const std_shared_ptr< IFunStack > &fun_stack ): funStack( fun_stack ) {
	renderWidget = new QWidget( );
	renderImage = new QImage( 50, 150, QImage::Format_RGBA8888 );
	renderWidget->render( renderImage );
	renderWidget->hide( );
}
NodeGeneraterItem::~NodeGeneraterItem( ) {
	delete renderImage;
	delete renderWidget;
}
