#include "pointNodeRunLink.h"

#include "../../../../enums/nodeEnum.h"

#include "../../../../tools/NodeRunLinkTools.h"
#include "../../../../tools/vectorTools.h"

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
	empty = resultRefNodeVector.size( ) == 0;
	return true;
}
bool PointNodeRunLink::sortBilderList( const std::vector< Node * > &reference_sort_vector ) {
	auto beg = getBeforeNode( );
	if( empty == false && NodeRunLink::sortBilderList( reference_sort_vector ) == false )
		if( beg == nullptr )
			return false;
	auto &startNodeVector = get->getStartNodeVector( );
	size_t index;
	if( VectorTools::findIndex( startNodeVector, beg, index ) == false )
		startNodeVector.emplace_back( beg );
	return true;
}
