#include "./nodeInputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include "../../../generate/varGenerate.h"

#include "../../../tools/tools.h"

#include "../../../varType/I_Type.h"
#include "../../../varType/I_Var.h"

#include "../../../widgets/mainWidget.h"

#include "../../item/nodeItem.h"

Imp_StaticMetaInfo( NodeInputPort, QObject::tr( "NodeInputPort" ), QObject::tr( "inputProt" ) );

bool NodeInputPort::updateProtLayout( ) {
	return renderLayout( false );
}
bool NodeInputPort::linkOutputPort( NodePort *output_port ) {
	
	return true;
}
bool NodeInputPort::disLinkOutputPor( NodePort *remove_output_port ) {
	return false;
}
bool NodeInputPort::getPos( QPoint &result_pos ) const {
	return parentItem->getInputPortPos( this, result_pos );
}
