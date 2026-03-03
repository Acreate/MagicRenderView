#include "createNodeRunLink.h"

#include <enums/nodeEnum.h>

#include "../../nodeRunLinkData.h"

#include "../../../../tools/NodeRunLinkTools.h"
#include "../../../../tools/nodeTools.h"

#include "../../../node/node.h"
CreateNodeRunLink::CreateNodeRunLink( Node *const init_node_ptr ) : NodeRunLink( init_node_ptr ) { }

bool CreateNodeRunLink::builder( ) {
	Node *beforeNode = getBeforeNode( );
	if( beforeNode == nullptr )
		return false;
	NodeEnum::NodeType targetNodeType = NodeEnum::NodeType::Create;
	if( beforeNode->getNodeType( ) != targetNodeType )
		return false;

	auto &resultRefNodeVector = get->getLinkNodeVector( );
	if( get->getNodeRef( resultRefNodeVector ) == false )
		return false;
	return true;
}
bool CreateNodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return NodeRunLink::linkHasNode( check_node_ptr );
}
