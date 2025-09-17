#include "./nodeInputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include "../../../tools/tools.h"

#include "../../item/nodeItem.h"

Imp_StaticMetaInfo( NodeInputPort, QObject::tr( "NodeInputPort" ), QObject::tr( "inputProt" ) );

bool NodeInputPort::updateProtLayout( ) {
	return renderLayout( false );
}
void NodeInputPort::linkOutputPort( NodeOutputPort *output_port ) {
	linkOutputVector.emplace_back( output_port );
	connect( output_port, &NodeOutputPort::outputPorDelete, this, &NodeInputPort::disLinkOutputPor );
	emit linkOutputPorOver( output_port );
}
void NodeInputPort::disLinkOutputPor( NodeOutputPort *remove_output_port ) {
	size_t count = linkOutputVector.size( );
	auto vectorPtr = linkOutputVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( vectorPtr[ index ] == remove_output_port ) {
			linkOutputVector.erase( linkOutputVector.begin( ) + index );
			disconnect( remove_output_port, &NodeOutputPort::outputPorDelete, this, &NodeInputPort::disLinkOutputPor );
			emit disLinkOutputPorOver( remove_output_port );
			return;
		}
}
bool NodeInputPort::getPos( QPoint &result_pos ) const {
	return parentItem->getInputPortPos( this, result_pos );
}
