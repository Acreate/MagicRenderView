#include "./NodePort.h"
#include <qt/node/item/nodeItem.h>

Imp_StaticMetaInfo( NodePort, QObject::tr( "NodeOutputPort" ), QObject::tr( "outputProt" ) )
NodePort::NodePort( NodeItem *parent ) : QObject( parent ), var( nullptr ), nodePortRender( QImage( 16, 16, QImage::Format_RGBA8888 ) ) {
}
QPoint NodePort::converToNodeItemWidgetPos( ) const {
	return nodePos + parent->getPos( );
}
QRect NodePort::converToNodeItemWidgetGeometry( ) const {
	return QRect( nodePos + parent->getPos( ), nodeSize );
}
