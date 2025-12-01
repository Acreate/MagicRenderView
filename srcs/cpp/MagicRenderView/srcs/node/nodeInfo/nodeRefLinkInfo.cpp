#include "nodeRefLinkInfo.h"

#include <QMenu>

#include "nodePortLinkInfo.h"

#include "../../srack/srackInfo.h"

#include "../../widget/drawNodeWidget.h"

#include "../node/node.h"

#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"
void NodeRefLinkInfo::linkRelease( NodeRefLinkInfo *release_target_node_ref_link_info ) {

	removeInputNodeRef( release_target_node_ref_link_info );
	removeOutputNodeRef( release_target_node_ref_link_info );

}
void NodeRefLinkInfo::removeInputNodeRef( NodeRefLinkInfo *remove ) {
	size_t count = refInputVector.size( );
	auto nodeRefLinkInfo = refInputVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( nodeRefLinkInfo[ index ] == remove ) {
			refInputVector.erase( refInputVector.begin( ) + index );
			break;
		}
}
void NodeRefLinkInfo::removeOutputNodeRef( NodeRefLinkInfo *remove ) {
	size_t count = refOutputVector.size( );
	auto nodeRefLinkInfo = refOutputVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( nodeRefLinkInfo[ index ] == remove ) {
			nodePortLinkInfo->removeNodeRefLinkInfoLinkTarget( remove );
			refOutputVector.erase( refOutputVector.begin( ) + index );
			break;
		}
}
NodeRefLinkInfo::NodeRefLinkInfo( Node *current_node ) : currentNode( current_node ) {
	currentNode->nodeRefLinkInfoPtr = this;
	managementLinkMenu = new QMenu( );
	nodePortLinkInfo = new NodePortLinkInfo( this, managementLinkMenu );
	auto addAction = managementLinkMenu->addAction( QString( tr( "删除 [%1] 节点" ) ).arg( current_node->nodeName ) );
	connect( addAction, &QAction::triggered, [this]( ) {
		delete currentNode;
	} );
}
NodeRefLinkInfo::~NodeRefLinkInfo( ) {
	emit release_NodeRefLinkInfo_signal( this, Create_SrackInfo( ) );
	delete managementLinkMenu;
	delete nodePortLinkInfo;
}
bool NodeRefLinkInfo::appendInputRef( OutputPort *output_port, NodeRefLinkInfo *in_put_ref, InputPort *input_port ) {
	if( nodePortLinkInfo->hasPortRef( output_port, input_port ) )
		return true;
	if( nodePortLinkInfo->appEndLinkTarget( output_port, input_port ) == false )
		return false;
	QString removeLinkText( tr( "删除 [%1.%2] -> [%3.%4] 链接" ) );
	removeLinkText = removeLinkText.arg( output_port->getParentNode( )->nodeName ).arg( output_port->getPortName( ) ).arg( input_port->getParentNode( )->nodeName ).arg( input_port->getPortName( ) );
	auto addAction = in_put_ref->managementLinkMenu->addAction( removeLinkText );
	connect( addAction, &QAction::triggered, [addAction, this, output_port, in_put_ref, input_port]( ) {
		removeInputRef( output_port, in_put_ref, input_port );
		addAction->deleteLater( );
		drawNodeWidget->update( );
	} );
	size_t count = refInputVector.size( );
	auto refInputVectorPtr = refInputVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( refInputVectorPtr[ index ] == in_put_ref )
			return true;
	if( index == count ) {
		refInputVector.emplace_back( in_put_ref );

		count = in_put_ref->refOutputVector.size( );
		refInputVectorPtr = in_put_ref->refOutputVector.data( );
		for( index = 0; index < count; ++index )
			if( refInputVectorPtr[ index ] == this )
				break;
		if( index == count )
			in_put_ref->refOutputVector.emplace_back( this );

		connect( this, &NodeRefLinkInfo::release_NodeRefLinkInfo_signal, in_put_ref, &NodeRefLinkInfo::linkRelease );
		connect( in_put_ref, &NodeRefLinkInfo::release_NodeRefLinkInfo_signal, this, &NodeRefLinkInfo::linkRelease );
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
	disconnect( this, &NodeRefLinkInfo::release_NodeRefLinkInfo_signal, in_put_ref, &NodeRefLinkInfo::linkRelease );
	disconnect( in_put_ref, &NodeRefLinkInfo::release_NodeRefLinkInfo_signal, this, &NodeRefLinkInfo::linkRelease );
	return true;
}
bool NodeRefLinkInfo::hasLinkInfo( OutputPort *output_port, InputPort *input_port ) {
	return nodePortLinkInfo->hasPortRef( output_port, input_port );
}
