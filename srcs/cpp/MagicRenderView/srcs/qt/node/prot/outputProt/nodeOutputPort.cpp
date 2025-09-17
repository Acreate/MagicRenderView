#include "./nodeOutputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include "../../../tools/tools.h"

#include "../../item/nodeItem.h"

Imp_StaticMetaInfo( NodeOutputPort, QObject::tr( "NodeOutputPort" ), QObject::tr( "outputProt" ) );
bool NodeOutputPort::updateProtLayout( ) {
	return renderLayout( true );
}
bool NodeOutputPort::getPos( QPoint &result_pos ) const {
	return parentItem->getOutputPortPos( this, result_pos );
}
