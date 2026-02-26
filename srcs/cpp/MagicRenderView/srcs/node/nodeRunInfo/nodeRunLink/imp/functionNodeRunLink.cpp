#include "functionNodeRunLink.h"

#include "../../../../enums/nodeEnum.h"

#include "../../../../tools/NodeRunLinkTools.h"

#include "../../../node/node.h"
bool FunctionNodeRunLink::builder( ) {

	Node *beforeNode = getBeforeNode( );
	if( beforeNode == nullptr )
		return false;
	NodeEnum::NodeType targetNodeType = NodeEnum::NodeType::Function;
	if( beforeNode->getNodeType( ) != targetNodeType )
		return false;

	auto &resultRefNodeVector = get->getLinkNodeVector( );
	if( get->getNodeOutputInForRef( resultRefNodeVector ) == false )
		return false;
	auto &startNodeVector = get->getStartNodeVector( );
	startNodeVector.clear( );
	size_t count = resultRefNodeVector.size( );
	auto data = resultRefNodeVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] && data[ index ]->getNodeType( ) == targetNodeType )
			startNodeVector.emplace_back( data[ index ] );
	return true;
}
bool FunctionNodeRunLink::getNextRunNode( const std::vector< Node * > &over_run_node_vector, Node *&result_next_node_ptr ) {
	if( isOver( ) )
		return false;
	return true;
}
