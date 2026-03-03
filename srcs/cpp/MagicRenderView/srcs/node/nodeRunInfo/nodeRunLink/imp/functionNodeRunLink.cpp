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

	return true;
}
bool FunctionNodeRunLink::sortBilderList( const std::vector< Node * > &reference_sort_vector ) {
	if( NodeRunLink::sortBilderList( reference_sort_vector ) == false )
		return false;
	auto &startNodeVector = get->getStartNodeVector( );
	startNodeVector.emplace_back( getBeforeNode( ) );
	return true;
}
