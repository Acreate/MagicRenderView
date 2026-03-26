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
	if( filterDeprecatedNode( resultRefNodeVector ) == false )
		return false;
	return true;
}
bool PointNodeRunLink::sortBilderList( const std::vector< Node * > &reference_sort_vector ) {
	if( NodeRunLink::sortBilderList( reference_sort_vector ) == false )
		return false;
	auto &startNodeVector = get->getStartNodeVector( );
	startNodeVector.emplace_back( getBeforeNode( ) );
	return true;
}
