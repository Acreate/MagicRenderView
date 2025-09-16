#include "./nodeInputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include "../../../tools/tools.h"

Imp_StaticMetaInfo( NodeInputPort, QObject::tr( "NodeInputPort" ), QObject::tr( "inputProt" ) );

bool NodeInputPort::updateProtLayout( ) {
	return renderLayout( ":/ico/info_node.png", false );
}
