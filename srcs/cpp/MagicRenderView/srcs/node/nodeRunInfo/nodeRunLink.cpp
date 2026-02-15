#include "nodeRunLink.h"

#include "../../enums/nodeEnum.h"

#include "../node/node.h"

#include "nodeRunLinkData/nodeRunLinkData.h"

NodeRunLink::~NodeRunLink( ) {
	delete nodeRunLinkDataPtr;
}
NodeRunLinkData * NodeRunLink::getNodeRunLinkDataPtr( ) const {
	return nodeRunLinkDataPtr;
}
NodeRunLink::NodeRunLink( Node *const init_node_ptr ) {
	nodeRunLinkDataPtr = new NodeRunLinkData( init_node_ptr );
}
bool NodeRunLink::isReady( ) const {
	return nodeRunLinkDataPtr->ready;
}
bool NodeRunLink::isOver( ) const {
	return nodeRunLinkDataPtr->over;
}
Node * NodeRunLink::getStartNode( ) const {
	return nodeRunLinkDataPtr->startNode;
}
Node * NodeRunLink::getCurrentNode( ) const {
	return nodeRunLinkDataPtr->currentNode;
}
Node * NodeRunLink::getBeforeNode( ) const {
	return nodeRunLinkDataPtr->beforeNode;
}
bool NodeRunLink::adviseRunNode( const Node *const node ) const {
	Node **refNodeData;
	size_t overCount;
	Node *const*overNodeData;
	size_t overIndex;
	size_t refNodeIndex;
	NodeEnum::NodeType nodeType;
	std::vector< Node * > refNodeVector;
	size_t refNodeCount;
	nodeType = node->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Point :
			return true;
			break;
	}
	refNodeVector = node->getOtherNodeOutputPortRefThisNodeInputPortVector( );
	refNodeCount = refNodeVector.size( );
	if( refNodeCount ) {
		refNodeData = refNodeVector.data( );
		overCount = nodeRunLinkDataPtr->overRunNodeVector.size( );
		overNodeData = nodeRunLinkDataPtr->overRunNodeVector.data( );
		for( refNodeIndex = 0; refNodeIndex < refNodeCount; ++refNodeIndex ) {
			nodeType = refNodeData[ refNodeIndex ]->getNodeType( );
			if( nodeType == NodeEnum::NodeType::Point )
				continue;
			for( overIndex = 0; overIndex < overCount; ++overIndex )
				if( refNodeData[ refNodeIndex ] == overNodeData[ overIndex ] )
					break;
			if( overIndex == overCount )
				return false; // 依赖未能完全调用
		}
		if( refNodeIndex != refNodeCount )
			return false; // 依赖未能完全调用
	}
	return true;
}

bool NodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	size_t count = nodeRunLinkDataPtr->linkNodeVector.size( );
	if( count == 0 )
		return false;
	auto data = nodeRunLinkDataPtr->linkNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == check_node_ptr )
			return true;
	return false;
}
