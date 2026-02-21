#include "createNodeRunLink.h"

#include <enums/nodeEnum.h>

#include "../../../node/node.h"
CreateNodeRunLink::CreateNodeRunLink( Node *const init_node_ptr ) : NodeRunLink( init_node_ptr ) { }

bool CreateNodeRunLink::builder( ) {
	if( getBeforeNode( )->getNodeType( ) != NodeEnum::NodeType::Create )
		return false;
	return false;
}

bool CreateNodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return false;
}
bool CreateNodeRunLink::getNextRunNode( const std::vector< Node * > &over_run_node_vector, Node *&result_next_node_ptr ) {
	return false;
}
