#include "nodeRefLinkInfo.h"

#include "nodePortLinkInfo.h"

#include "../node/node.h"

#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"
NodeRefLinkInfo::NodeRefLinkInfo( Node *current_node ) : currentNode( current_node ), nodePortLinkInfo( new NodePortLinkInfo( this ) ) {
	currentNode->nodeRefLinkInfoPtr = this;
}
NodeRefLinkInfo::~NodeRefLinkInfo( ) {
	delete nodePortLinkInfo;
}
bool NodeRefLinkInfo::appendInputRef( OutputPort *output_port, NodeRefLinkInfo *in_put_ref, InputPort *input_port ) {
	if( in_put_ref->currentNode->hasInputPort( input_port ) == false )
		return false;
	if( nodePortLinkInfo->appEndLinkTarget( output_port, input_port ) == false )
		return false;
	size_t count = refInputVector.size( );
	auto refInputVectorPtr = refInputVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == in_put_ref )
			return true;
	if( index == count )
		refInputVector.emplace_back( in_put_ref );

	count = in_put_ref->refOutputVector.size( );
	refInputVectorPtr = in_put_ref->refOutputVector.data( );
	for( index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == this )
			break;
	if( index == count )
		in_put_ref->refOutputVector.emplace_back( this );
	return true;
}
bool NodeRefLinkInfo::removeInputRef( OutputPort *output_port, NodeRefLinkInfo *in_put_ref, InputPort *input_port ) {
	if( in_put_ref->currentNode->hasInputPort( input_port ) == false )
		return false;
	if( nodePortLinkInfo->removeLinkTarget( output_port, input_port ) == false )
		return false;
	if( nodePortLinkInfo->hasNodeRef( in_put_ref ) == true )
		return true;

	size_t count = refInputVector.size( );
	auto refInputVectorPtr = refInputVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == in_put_ref ) {
			refInputVector.erase( refInputVector.begin( ) + index );
			break;
		}

	count = in_put_ref->refOutputVector.size( );
	refInputVectorPtr = in_put_ref->refOutputVector.data( );
	for( index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == this ) {
			in_put_ref->refOutputVector.erase( in_put_ref->refOutputVector.begin( ) + index );
			break;
		}

	return true;
}
