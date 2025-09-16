#include "./nodeOutputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include "../../../tools/tools.h"

Imp_StaticMetaInfo( NodeOutputPort, QObject::tr( "NodeOutputPort" ), QObject::tr( "outputProt" ) );
bool NodeOutputPort::updateProtLayout( ) {
	return renderLayout( true );
}
