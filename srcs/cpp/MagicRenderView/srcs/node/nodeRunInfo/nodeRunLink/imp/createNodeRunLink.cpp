#include "createNodeRunLink.h"

#include <enums/nodeEnum.h>

#include "../../nodeRunLinkData.h"

#include "../../../../tools/NodeRunLinkTools.h"
#include "../../../../tools/nodeTools.h"
#include "../../../../tools/vectorTools.h"

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

	if( filterDeprecatedNode( resultRefNodeVector ) == false )
		return false;
	empty = resultRefNodeVector.size( ) == 0;
	return true;
}
bool CreateNodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return NodeRunLink::linkHasNode( check_node_ptr );
}
bool CreateNodeRunLink::sortBilderList( const std::vector< Node * > &reference_sort_vector ) {
	auto beforeNode = getBeforeNode( );
	if( empty == false && NodeRunLink::sortBilderList( reference_sort_vector ) == false )
		if( beforeNode == nullptr )
			return false;
	auto &startNodeVector = get->getStartNodeVector( );
	size_t index;
	if( VectorTools::findIndex( startNodeVector, beforeNode, index ) == false )
		startNodeVector.emplace_back( beforeNode );
	return true;
}
