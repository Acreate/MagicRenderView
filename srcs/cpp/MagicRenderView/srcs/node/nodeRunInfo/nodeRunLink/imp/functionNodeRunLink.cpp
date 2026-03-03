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
