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
	connect( nodePortLinkInfo, &NodePortLinkInfo::create_link_signal, this, &NodeRefLinkInfo::create_port_link_signal );
	connect( nodePortLinkInfo, &NodePortLinkInfo::release_link_signal, this, &NodeRefLinkInfo::release_port_link_signal );
}
NodeRefLinkInfo::~NodeRefLinkInfo( ) {
	size_t count;
	NodeRefLinkInfo **refInputArrayPtr;
	size_t index;
	size_t refOutputCount;
	size_t refIndex;
	NodeRefLinkInfo **foreachNodeRefArrayPtr;
	NodeRefLinkInfo *checkNodeRefPtr;

	count = refInputVector.size( );
	refInputArrayPtr = refInputVector.data( );
	for( index = 0; index < count; ++index ) {
		checkNodeRefPtr = refInputArrayPtr[ index ];
		auto &refOutputVector = checkNodeRefPtr->refOutputVector;
		refOutputCount = refOutputVector.size( );
		foreachNodeRefArrayPtr = refOutputVector.data( );
		for( refIndex = 0; refIndex < refOutputCount; ++refIndex ) {
			if( foreachNodeRefArrayPtr[ refIndex ] == this ) {
				//auto runResult = checkNodeRefPtr->nodePortLinkInfo->removeNodeRefLinkInfoLinkTarget( this );
				//Application::getInstancePtr( )->getPrinterDirector( )->info( "%1", { QString( runResult ? "true" : "false" ) }, Create_SrackInfo( ) );
				refOutputVector.erase( refOutputVector.begin( ) + refIndex );
				//emit release_node_link_signal( this, input_port, out_put_ref, output_port );
				break;
			}

		}
	}
	refOutputCount = refOutputVector.size( );
	foreachNodeRefArrayPtr = refOutputVector.data( );
	for( refIndex = 0; refIndex < refOutputCount; ++refIndex ) {
		checkNodeRefPtr = foreachNodeRefArrayPtr[ refIndex ];
		auto &refInputVector = checkNodeRefPtr->refInputVector;
		count = refInputVector.size( );
		foreachNodeRefArrayPtr = refInputVector.data( );
		for( index = 0; index < count; ++index ) {
			if( foreachNodeRefArrayPtr[ index ] == this ) {
				auto runResult = checkNodeRefPtr->nodePortLinkInfo->removeNodeRefLinkInfoLinkTarget( this );
				Application::getInstancePtr( )->getPrinterDirector( )->info( "%1", { QString( runResult ? "true" : "false" ) }, Create_SrackInfo( ) );
				refInputVector.erase( refInputVector.begin( ) + index );
				//emit release_node_link_signal( this, input_port, out_put_ref, output_port );
				break;
			}

		}
	}
	// 删除包含对象
	delete nodePortLinkInfo;
}
bool NodeRefLinkInfo::appendInputRef( InputPort *input_port, OutputPort *output_port ) {

	if( nodePortLinkInfo->appEndLinkInputTarget( input_port, output_port ) == false )
		return false;
	auto outNodeRef = output_port->parentNode->nodeRefLinkInfoPtr;
	size_t count = refInputVector.size( );
	auto refInputVectorPtr = refInputVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == outNodeRef )
			return true;
	if( index == count ) {
		refInputVector.emplace_back( outNodeRef );
		outNodeRef->refOutputVector.emplace_back( this );
		emit create_node_link_signal( this, outNodeRef, Create_SrackInfo( ) );
	}

	return true;
}
bool NodeRefLinkInfo::removeInputRef( InputPort *input_port, OutputPort *output_port ) {

	if( nodePortLinkInfo->removeLinkInputTarget( input_port, output_port ) == false )
		return false;
	auto outNodeRef = output_port->parentNode->nodeRefLinkInfoPtr;
	if( nodePortLinkInfo->hasNodeRef( outNodeRef ) == true )
		return true;

	size_t count = refInputVector.size( );
	auto refInputVectorPtr = refInputVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == outNodeRef ) {
			refInputVector.erase( refInputVector.begin( ) + index );
			count = outNodeRef->refOutputVector.size( );
			refInputVectorPtr = outNodeRef->refOutputVector.data( );
			for( index = 0; index < count; ++index )
				if( refInputVectorPtr[ index ] == this ) {
					outNodeRef->refOutputVector.erase( outNodeRef->refOutputVector.begin( ) + index );
					emit release_node_link_signal( this, outNodeRef, Create_SrackInfo( ) );
					return true;
				}
			return false;
		}

	return false;
}
bool NodeRefLinkInfo::hasInputNodeRef( NodeRefLinkInfo *in_put_ref ) {
	auto count = refInputVector.size( );
	auto refInputVectorPtr = refInputVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == in_put_ref )
			return true;;
	return false;
}
bool NodeRefLinkInfo::hasPortRef( InputPort *input_port, OutputPort *output_port ) {
	return nodePortLinkInfo->hasPortRef( input_port, output_port );
}
