#include "nodePortLinkInfo.h"

#include "nodeRefLinkInfo.h"

#include "../port/outputPort/outputPort.h"
NodePortLinkInfo::NodePortLinkInfo( NodeRefLinkInfo *node_ref_link_info, QMenu *management_link_menu ) : nodeRefLinkInfo( node_ref_link_info ), managementLinkMenu( management_link_menu ) { }
bool NodePortLinkInfo::appEndLinkTarget( OutputPort *out_put_port, InputPort *in_put_port ) {
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
void NodePortLinkInfo::removeNodeRefLinkInfoLinkTarget( NodeRefLinkInfo *remove_all_port_node_ref_link_info ) {

	auto findNode = remove_all_port_node_ref_link_info->currentNode;

	std::pair< InputPort *, std::vector< OutputPort * > > *inputPortArrayPtr;
	size_t inputPortCount;
	inputPortArrayPtr = inputPortVector.data( );
	inputPortCount = inputPortVector.size( );
	size_t inputPortindex;
	size_t foreachOutputCount;
	OutputPort **foreachOutputArrayPtr;
	size_t foreachOutputIndex;

	for( inputPortindex = 0; inputPortindex < inputPortCount; inputPortindex += 1 ) {
		auto &outputPorts = inputPortArrayPtr[ inputPortindex ].second;
		foreachOutputCount = outputPorts.size( );
		foreachOutputArrayPtr = outputPorts.data( );
		for( foreachOutputIndex = 0; foreachOutputIndex < foreachOutputCount; foreachOutputIndex += 1 )
			if( foreachOutputArrayPtr[ foreachOutputIndex ]->getParentNode( ) == findNode ) {
				if( foreachOutputCount == 1 ) {
					inputPortVector.erase( inputPortVector.begin( ) + inputPortindex );
					inputPortArrayPtr = inputPortVector.data( );
					inputPortCount = inputPortVector.size( );
					inputPortindex -= 1;
					break;
				}
				outputPorts.erase( outputPorts.begin( ) + foreachOutputIndex );
				foreachOutputCount = outputPorts.size( );
				foreachOutputArrayPtr = outputPorts.data( );
				foreachOutputIndex -= 1;
			}
	}
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
bool NodePortLinkInfo::hasPortRef( const OutputPort *out_put_port, const InputPort *in_put_port ) const {
	size_t count = inputPortVector.size( );
	auto data = inputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( data[ index ].first == in_put_port ) {
			count = data[ index ].second.size( );
			auto foreachData = data[ index ].second.data( );
			for( index = 0; index < count; ++index )
				if( foreachData[ index ] == out_put_port )
					return true;
			break;
		}

	return false;
}
