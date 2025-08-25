#include "./nodeGeneraterItem.h"

#include <QPainter>

#include "../widgets/nodeGeneraterListWidget.h"

NodeGeneraterItem::NodeGeneraterItem( const std_shared_ptr< IFunStack > &fun_stack ) : funStack( fun_stack ) {
	renderWidget = nullptr;
	renderImage = nullptr;
}
NodeGeneraterItem::~NodeGeneraterItem( ) {
	if( renderImage )
		delete renderImage;
	if( renderWidget )
		delete renderWidget;
}
