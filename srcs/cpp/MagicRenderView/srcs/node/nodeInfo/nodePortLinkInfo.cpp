#include "nodePortLinkInfo.h"

#include "nodeRefLinkInfo.h"

#include "../port/outputPort/outputPort.h"
NodePortLinkInfo::NodePortLinkInfo( NodeRefLinkInfo *node_ref_link_info ) : nodeRefLinkInfo( node_ref_link_info ) { }
bool NodePortLinkInfo::appEndLinkTarget( OutputPort *out_put_port, InputPort *in_put_port ) {
	if( nodeRefLinkInfo == nullptr )
		return false;
	if( nodeRefLinkInfo->currentNode->hasInputPort( in_put_port ) == false )
		return false;
	size_t count = inputPortVector.size( );
	auto data = inputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( data[ index ].first == in_put_port ) {
			auto &outputPorts = data[ index ].second;
			auto outputPortArrayPtr = outputPorts.data( );
			count = outputPorts.size( );
			for( index = 0; index < count; ++index )
				if( outputPortArrayPtr[ index ] == out_put_port )
					return true;
			outputPorts.emplace_back( out_put_port );
			return true;
		}
	std::vector< OutputPort * > ports;
	ports.emplace_back( out_put_port );
	inputPortVector.emplace_back( std::pair( in_put_port, ports ) );
	return true;
}
bool NodePortLinkInfo::removeLinkTarget( OutputPort *out_put_port, InputPort *in_put_port ) {
	if( nodeRefLinkInfo == nullptr )
		return false;
	if( nodeRefLinkInfo->currentNode->hasInputPort( in_put_port ) == false )
		return false;
	size_t count = inputPortVector.size( );
	auto data = inputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( data[ index ].first == in_put_port ) {
			auto &outputPorts = data[ index ].second;
			auto outputPortArrayPtr = outputPorts.data( );
			count = outputPorts.size( );
			for( index = 0; index < count; ++index )
				if( outputPortArrayPtr[ index ] == out_put_port ) {
					if( count == 1 )
						inputPortVector.erase( inputPortVector.begin( ) + index );
					else
						outputPorts.erase( outputPorts.begin( ) + index );
					return true;
				}
			return false;
		}
	return false;
}
bool NodePortLinkInfo::hasNodeRef( const NodeRefLinkInfo *check_node_ref ) const {
	auto currentNode = check_node_ref->currentNode;
	size_t count = inputPortVector.size( );
	auto data = inputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index ) {
		auto &outputPorts = data[ index ].second;
		auto outputPortArrayPtr = outputPorts.data( );
		count = outputPorts.size( );
		for( index = 0; index < count; ++index )
			if( outputPortArrayPtr[ index ]->getParentNode( ) == currentNode )
				return true;
		return false;
	}
	return false;
}
