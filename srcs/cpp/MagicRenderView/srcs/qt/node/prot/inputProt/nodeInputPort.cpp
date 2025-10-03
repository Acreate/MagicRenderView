#include "./nodeInputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include "../../../tools/tools.h"

#include "../../../widgets/mainWidget.h"

#include "../../item/nodeItem.h"

Imp_StaticMetaInfo( NodeInputPort, QObject::tr( "NodeInputPort" ), QObject::tr( "inputProt" ) );

bool NodeInputPort::updateProtLayout( ) {
	return renderLayout( false );
}
bool NodeInputPort::linkOutputPort( NodePort *output_port ) {
	auto parentItem = output_port->getParentItem( );
	// 检查是否存在重复链接
	size_t count = overrideLink.size( );
	auto data = overrideLink.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == output_port )
			return true; // 已经链接
	overrideLink.emplace_back( output_port );
	auto nodeItemGenerateCode = parentItem->getGenerateCode( );
	auto nodePortName = output_port->getTitle( );

	linkOutputVector.emplace_back( nodeItemGenerateCode, nodePortName );
	connect( output_port, &NodeOutputPort::outputPorDelete, this, &NodeInputPort::disLinkOutputPor );
	emit linkOutputPorOver( output_port );
	return true;
}
bool NodeInputPort::disLinkOutputPor( NodePort *remove_output_port ) {
	size_t count = linkOutputVector.size( );
	if( count == 0 )
		return false;

	auto removeParentItem = remove_output_port->getParentItem( );
	if( removeParentItem == nullptr )
		return false;
	auto vectorPtr = linkOutputVector.data( );
	auto removeOutputPortName = remove_output_port->getTitle( );
	size_t generaterCode = removeParentItem->getGenerateCode( );

	for( size_t index = 0; index < count; ++index )
		if( vectorPtr[ index ].second == removeOutputPortName && generaterCode == vectorPtr[ index ].first ) {
			linkOutputVector.erase( linkOutputVector.begin( ) + index );
			disconnect( remove_output_port, &NodeOutputPort::outputPorDelete, this, &NodeInputPort::disLinkOutputPor );
			count = overrideLink.size( );
			auto data = overrideLink.data( );
			index = 0;
			for( ; index < count; ++index )
				if( data[ index ] == remove_output_port )
					overrideLink.erase( overrideLink.begin( ) + index );
			emit disLinkOutputPorOver( remove_output_port );
			return true;
		}
	return false;
}
bool NodeInputPort::getPos( QPoint &result_pos ) const {
	return parentItem->getInputPortPos( this, result_pos );
}
