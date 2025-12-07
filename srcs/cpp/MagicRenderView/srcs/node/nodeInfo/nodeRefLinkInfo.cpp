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

void NodeRefLinkInfo::clearInfo( ) {
	refInputVector.clear( );
	refOutputVector.clear( );
	nodePortLinkInfo->clearLink( );
}
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
	for( index = 0; index < count; ++index )
		refInputArrayPtr[ index ]->removeOutputNodeRef( this );

	refOutputCount = refOutputVector.size( );
	foreachNodeRefArrayPtr = refOutputVector.data( );
	for( refIndex = 0; refIndex < refOutputCount; ++refIndex )
		foreachNodeRefArrayPtr[ refIndex ]->removeInputNodeRef( this );
	currentNode->nodeRefLinkInfoPtr = nullptr;
	// 删除包含对象
	delete nodePortLinkInfo;
}
bool NodeRefLinkInfo::hasInputRefNode( NodeRefLinkInfo *node_ref_link_info ) {
	size_t count = refInputVector.size( );
	auto refInputVectorPtr = refInputVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == node_ref_link_info || refInputVectorPtr[ index ]->hasInputRefNode( node_ref_link_info ) )
			return true;
	return false;
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
bool NodeRefLinkInfo::removeInputNodeRef( NodeRefLinkInfo *remove_target ) {
	size_t count = refInputVector.size( );
	if( count == 0 )
		return false;
	auto nodeRefLinkInfoArrayPtr = refInputVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( nodeRefLinkInfoArrayPtr[ index ] == remove_target ) {
			nodePortLinkInfo->removeNodeRefLinkInfoLinkTarget( remove_target );
			refInputVector.erase( refInputVector.begin( ) + index );
			return true;
		}
	return false;
}
bool NodeRefLinkInfo::removeOutputNodeRef( NodeRefLinkInfo *remove_target ) {
	size_t count = refOutputVector.size( );
	if( count == 0 )
		return false;
	auto nodeRefLinkInfoArrayPtr = refOutputVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( nodeRefLinkInfoArrayPtr[ index ] == remove_target ) {
			refOutputVector.erase( refOutputVector.begin( ) + index );
			return true;
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
