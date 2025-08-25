#include "./nodeGeneraterItem.h"

#include <QPainter>

#include <qt/nodes/nodeWidget/INodeWidget.h>

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
