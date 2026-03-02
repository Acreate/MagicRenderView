#include "pointNodeRunLink.h"

#include "../../../../enums/nodeEnum.h"

#include "../../../../tools/NodeRunLinkTools.h"

#include "../../../node/node.h"
bool PointNodeRunLink::builder( ) {
	Node *beforeNode = getBeforeNode( );
	if( beforeNode == nullptr )
		return false;
	NodeEnum::NodeType targetNodeType = NodeEnum::NodeType::Point;
	if( beforeNode->getNodeType( ) != targetNodeType )
		return false;

	auto &resultRefNodeVector = get->getLinkNodeVector( );
	if( get->getNodeOutputInForRef( resultRefNodeVector ) == false )
		return false;
	return true;
}
bool PointNodeRunLink::getNextRunNode( const std::vector< Node * > &over_run_node_vector, Node *&result_next_node_ptr ) {
	if( isOver( ) )
		return false;
	return true;
}
