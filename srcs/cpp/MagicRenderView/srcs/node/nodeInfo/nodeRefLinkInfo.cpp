#include "nodeRefLinkInfo.h"

#include <QMenu>

#include "nodePortLinkInfo.h"

#include "../../app/application.h"

#include "../../director/printerDirector.h"

#include "../../srack/srackInfo.h"

#include "../../widget/drawNodeWidget.h"

#include "../node/node.h"

#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"

NodeRefLinkInfo::NodeRefLinkInfo( Node *current_node ) : currentNode( current_node ) {
	currentNode->nodeRefLinkInfoPtr = this;
	nodePortLinkInfo = new NodePortLinkInfo( this );
}
NodeRefLinkInfo::~NodeRefLinkInfo( ) {
	size_t count;
	NodeRefLinkInfo **refInputArrayPtr;
	size_t index;
	size_t refOutputCount;
	size_t refIndex;
	count = refInputVector.size( );
	refInputArrayPtr = refInputVector.data( );
	NodeRefLinkInfo **refOutputArrayPtr;
	NodeRefLinkInfo *checkNodeRefPtr;
	for( index = 0; index < count; ++index ) {
		checkNodeRefPtr = refInputArrayPtr[ index ];
		auto &refOutputVector = checkNodeRefPtr->refOutputVector;
		refOutputCount = refOutputVector.size( );
		refOutputArrayPtr = refOutputVector.data( );
		for( refIndex = 0; refIndex < refOutputCount; ++refIndex ) {
			if( refOutputArrayPtr[ refIndex ] == this ) {
				auto runResult = checkNodeRefPtr->nodePortLinkInfo->removeNodeRefLinkInfoLinkTarget( this );
				Application::getInstancePtr( )->getPrinterDirector( )->info( "%1", { QString( runResult ? "true" : "false" ) }, Create_SrackInfo( ) );
				refOutputVector.erase( refOutputVector.begin( ) + refIndex );
				break;
			}

		}
	}
	refOutputCount = refOutputVector.size( );
	refOutputArrayPtr = refOutputVector.data( );
	for( refIndex = 0; refIndex < refOutputCount; ++refIndex ) {
		checkNodeRefPtr = refOutputArrayPtr[ refIndex ];
		auto &refInputVector = checkNodeRefPtr->refInputVector;
		count = refInputVector.size( );
		refOutputArrayPtr = refInputVector.data( );
		for( index = 0; index < count; ++index ) {
			if( refOutputArrayPtr[ index ] == this ) {
				/*auto runResult = checkNodeRefPtr->nodePortLinkInfo->removeNodeRefLinkInfoLinkTarget( this );
				Application::getInstancePtr( )->getPrinterDirector( )->info( "%1", { QString( runResult ? "true" : "false" ) }, Create_SrackInfo( ) );*/
				refInputVector.erase( refInputVector.begin( ) + index );
				break;
			}

		}
	}
	// 删除包含对象
	delete nodePortLinkInfo;
}
bool NodeRefLinkInfo::appendInputRef( OutputPort *output_port, NodeRefLinkInfo *in_put_ref, InputPort *input_port ) {
	if( nodePortLinkInfo->hasPortRef( output_port, input_port ) )
		return true;
	if( nodePortLinkInfo->appEndLinkTarget( output_port, input_port ) == false )
		return false;

	size_t count = refInputVector.size( );
	auto refInputVectorPtr = refInputVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == in_put_ref )
			return true;
	if( index == count ) {
		refOutputVector.emplace_back( in_put_ref );
		in_put_ref->refInputVector.emplace_back( this );
	}

	return true;
}
bool NodeRefLinkInfo::removeInputRef( OutputPort *output_port, NodeRefLinkInfo *in_put_ref, InputPort *input_port ) {

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
bool NodeRefLinkInfo::hasLinkInfo( OutputPort *output_port, InputPort *input_port ) {
	return nodePortLinkInfo->hasPortRef( output_port, input_port );
}
