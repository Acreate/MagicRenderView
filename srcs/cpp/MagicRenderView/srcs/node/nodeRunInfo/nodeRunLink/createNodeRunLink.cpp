#include "createNodeRunLink.h"

#include "../../node/node.h"

#include "../nodeRunLinkData/nodeRunLinkData.h"
#include <enums/nodeEnum.h>
CreateNodeRunLink::CreateNodeRunLink( Node *const init_node_ptr ) : NodeRunLink( init_node_ptr ) { }

bool CreateNodeRunLink::builder( ) {
	auto nodeType = nodeRunLinkDataPtr->getBeforeNode( )->getNodeType( );
	if( nodeType != NodeEnum::NodeType::Create )
		return false;
	return false;
}

bool CreateNodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return false;
}
bool CreateNodeRunLink::getNextRunNode( Node *&result_next_node_ptr ) {
	return false;
}
