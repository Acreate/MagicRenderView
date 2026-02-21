#include "createNodeRunLink.h"

#include <enums/nodeEnum.h>

#include "../../../node/node.h"
CreateNodeRunLink::CreateNodeRunLink( Node *const init_node_ptr ) : NodeRunLink( init_node_ptr ) { }

bool CreateNodeRunLink::builder( ) {
	Node *beforeNode = getBeforeNode( );
	if( beforeNode == nullptr )
		return false;
	if( beforeNode->getNodeType( ) != NodeEnum::NodeType::Create )
		return false;
	return true;
}
bool CreateNodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return NodeRunLink::linkHasNode( check_node_ptr );
}
bool CreateNodeRunLink::getNextRunNode( const std::vector< Node * > &over_run_node_vector, Node *&result_next_node_ptr ) {
	if( isOver( ) )
		return false;
	return true;
}
