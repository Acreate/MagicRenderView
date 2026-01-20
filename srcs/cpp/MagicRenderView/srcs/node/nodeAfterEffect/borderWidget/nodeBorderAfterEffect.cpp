#include "nodeBorderAfterEffect.h"

#include <QPainter>

#include "nodeBorderDraw.h"
NodeBorderAfterEffect::NodeBorderAfterEffect( QWidget *parent, Qt::WindowFlags f ) : NodeAfterEffect( parent, f ) {
	nodeBorderDraw = new NodeBorderDraw( this );
}
NodeBorderAfterEffect::~NodeBorderAfterEffect( ) {
	delete nodeBorderDraw;
}
bool NodeBorderAfterEffect::updateLayout( ) {
	widgetToBottmLayer( );
	return true;
}
void NodeBorderAfterEffect::paintEvent( QPaintEvent *event ) {
	NodeAfterEffect::paintEvent( event );
	nodeBorderDraw->draw( );
}
