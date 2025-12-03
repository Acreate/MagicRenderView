#include "nodePortLinkInfo.h"

#include "inputportLinkOutputPortInfo.h"
#include "nodeRefLinkInfo.h"

#include "../../app/application.h"

#include "../../director/varDirector.h"

#include "../../srack/srackInfo.h"

#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"
NodePortLinkInfo::NodePortLinkInfo( NodeRefLinkInfo *node_ref_link_info ) : nodeRefLinkInfo( node_ref_link_info ) { }
bool NodePortLinkInfo::appEndLinkInputTarget( InputPort *in_put_port, OutputPort *out_put_port ) {
	size_t count = inputPortVector.size( );
	auto data = inputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( data[ index ]->getInputPort( ) == in_put_port ) {
			auto addendResult = data[ index ]->appendOutputPort( out_put_port );
			if( addendResult == false )
				return false;
			emit create_link_signal( in_put_port, out_put_port, Create_SrackInfo( ) );
			return true;
		}

	auto portLinkInfo = new InputportLinkOutputPortInfo( in_put_port );
	portLinkInfo->appendOutputPort( out_put_port );
	inputPortVector.emplace_back( portLinkInfo );
	emit create_link_signal( in_put_port, out_put_port, Create_SrackInfo( ) );
	return true;
}
bool NodePortLinkInfo::removeLinkInputTarget( InputPort *in_put_port, OutputPort *out_put_port ) {

	size_t count = inputPortVector.size( );
	auto data = inputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( data[ index ]->getInputPort( ) == in_put_port ) {
			if( data[ index ]->removeOutputPort( out_put_port ) == false )
				return false;
			if( data[ index ]->linkInputPortCount( ) == 0 ) {
				delete data[ index ];
				inputPortVector.erase( inputPortVector.begin( ) + index );
			}
			emit release_link_signal( in_put_port, out_put_port, Create_SrackInfo( ) );
			return true;
		}
	return false;
}
size_t NodePortLinkInfo::removeNodeRefLinkInfoLinkTarget( NodeRefLinkInfo *remove_all_port_node_ref_link_info ) {
	size_t result = 0;
	auto findNode = remove_all_port_node_ref_link_info->currentNode;

	InputportLinkOutputPortInfo * *inputPortArrayPtr;
	size_t inputPortCount;
	inputPortArrayPtr = inputPortVector.data( );
	inputPortCount = inputPortVector.size( );
	size_t inputPortindex;
	size_t foreachOutputCount;
	OutputPort *const*foreachOutputArrayPtr;
	size_t foreachOutputIndex;
	InputportLinkOutputPortInfo *inputportLinkOutputPortInfo;
	InputPort *inputPort;

	auto &outputPorts = findNode->getOutputPortVector( );
	foreachOutputCount = outputPorts.size( );
	foreachOutputArrayPtr = outputPorts.data( );

	for( foreachOutputIndex = 0; foreachOutputIndex < foreachOutputCount; foreachOutputIndex += 1 )
		for( inputPortindex = 0; inputPortindex < inputPortCount; inputPortindex += 1 ) {
			inputportLinkOutputPortInfo = inputPortArrayPtr[ inputPortindex ];
			if( inputportLinkOutputPortInfo->removeOutputPort( foreachOutputArrayPtr[ foreachOutputIndex ] ) == false )
				continue;
			inputPort = inputportLinkOutputPortInfo->getInputPort( );
			if( inputportLinkOutputPortInfo->linkInputPortCount( ) == 0 ) {
				delete inputportLinkOutputPortInfo;
				inputPortVector.erase( inputPortVector.begin( ) + inputPortindex );
				inputPortArrayPtr = inputPortVector.data( );
				inputPortCount = inputPortVector.size( );
				inputPortindex -= 1;
			}
			result += 1;
			emit release_link_signal( inputPort, foreachOutputArrayPtr[ foreachOutputIndex ], Create_SrackInfo( ) );
		}
	return result;
}
bool NodePortLinkInfo::hasNodeRef( const NodeRefLinkInfo *check_node_ref ) const {
	auto currentNode = check_node_ref->currentNode;
	return hasNodeRef( currentNode );
}
bool NodePortLinkInfo::hasNodeRef( const Node *check_node ) const {
	size_t count = inputPortVector.size( );
	auto data = inputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index ) {
		auto &outputPorts = data[ index ]->getOutputPortVector( );
		auto outputPortArrayPtr = outputPorts.data( );
		count = outputPorts.size( );
		for( index = 0; index < count; ++index )
			if( outputPortArrayPtr[ index ]->parentNode == check_node )
				return true;
		return false;
	}
	return false;
}
bool NodePortLinkInfo::hasPortRef( const InputPort *in_put_port, const OutputPort *out_put_port ) const {
	size_t count = inputPortVector.size( );
	auto data = inputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( data[ index ]->getInputPort( ) == in_put_port ) {
			auto &outputPorts = data[ index ]->getOutputPortVector( );
			count = outputPorts.size( );
			auto foreachData = outputPorts.data( );
			for( index = 0; index < count; ++index )
				if( foreachData[ index ] == out_put_port )
					return true;
			break;
		}

	return false;
}
NodePortLinkInfo::~NodePortLinkInfo( ) {
	size_t count = inputPortVector.size( );
	auto data = inputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete data[ index ];
}
bool NodePortLinkInfo::toUint8VectorData( size_t &result_use_count, std::vector< uint8_t > &result_vector_data ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	*uint64Ptr = 0;
	if( varDirector.toVector( uint64Ptr, result_vector_data ) == false )
		return false;
	return true;
}
