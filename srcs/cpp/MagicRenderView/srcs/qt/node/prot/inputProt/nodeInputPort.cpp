#include "./nodeInputPort.h"

#include <QPainter>

#include <qt/application/application.h>
#include <qt/node/item/nodeItem.h>

Imp_StaticMetaInfo( NodeInputPort, QObject::tr( "NodeInputPort" ), QObject::tr( "inputProt" ) );

bool NodeInputPort::updateProtLayout( ) {
	return renderLayout( false );
}

bool NodeInputPort::getPos( QPoint &result_pos ) const {
	return parentItem->getInputPortPos( this, result_pos );
}
