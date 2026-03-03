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
bool CreateNodeRunLink::sortBilderList( const std::vector< Node * > &reference_sort_vector ) {
	if( NodeRunLink::sortBilderList( reference_sort_vector ) == false )
		return false;
	auto &startNodeVector = get->getStartNodeVector( );
	auto &linkNodeVector = get->getLinkNodeVector( );
	size_t linkCout = linkNodeVector.size( );
	auto linkData = linkNodeVector.data( );
	size_t index = 0;
	for( ; index < linkCout; ++index )
		if( linkData[ index ]->getNodeType( ) == NodeEnum::NodeType::Create )
			startNodeVector.emplace_back( linkData[ index ] );
	return true;
}
