#include "nodeRunLinkData.h"

#include "../../enums/nodeEnum.h"

#include "../node/node.h"
NodeRunLinkData::NodeRunLinkData( Node *init_node_ptr ) {
	startNode = nullptr;
	currentNode = nullptr;
	beforeNode = init_node_ptr;
	over = false;
	ready = false;
}
bool NodeRunLinkData::isReady( ) const {
	return ready;
}
bool NodeRunLinkData::isOver( ) const {
	return over;
}
Node * NodeRunLinkData::getStartNode( ) const { return startNode; }
Node * NodeRunLinkData::getCurrentNode( ) const { return currentNode; }
Node * NodeRunLinkData::getBeforeNode( ) const { return beforeNode; }
const std::vector<Node *> & NodeRunLinkData::getOverRunNodeVector( ) const { return overRunNodeVector; }
const std::vector<Node *> & NodeRunLinkData::getLinkNodeVector( ) const { return linkNodeVector; }
const std::vector<Node *> & NodeRunLinkData::getAdviseNodeVector( ) const { return adviseNodeVector; }

bool NodeRunLinkData::adviseRunNode( const Node *const node ) const {
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
		overCount = overRunNodeVector.size( );
		overNodeData = overRunNodeVector.data( );
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

bool NodeRunLinkData::linkHasNode( const Node *const check_node_ptr ) const {
	size_t count = linkNodeVector.size( );
	if( count == 0 )
		return false;
	auto data = linkNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == check_node_ptr )
			return true;
	return false;
}
