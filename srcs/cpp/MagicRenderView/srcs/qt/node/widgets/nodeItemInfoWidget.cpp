#include "nodeItemInfoWidget.h"

#include <qmenu.h>

#include <qt/application/application.h>

#include <qt/node/director/nodeDirector.h>

NodeItemInfoWidget::NodeItemInfoWidget( NodeItem *node_item, QWidget *parent ) : QWidget( parent ), nodeItem( node_item ), renderBuff( new QImage( 0, 0, QImage::Format_RGBA8888 ) ) {
	applicationInstancePtr = Application::getApplicationInstancePtr( );
	nodeDirector = applicationInstancePtr->getNodeDirector( );
	nodeDirector->getNodeItemInfo( nodeItem, nodeItemInfoTarget );
}
NodeItemInfoWidget::~NodeItemInfoWidget( ) {
	emit releaseThisPtr( this );
	delete renderBuff;
}
void NodeItemInfoWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	*renderBuff = renderBuff->scaled( this->size( ) );
}
