#include "createNode.h"

#include "../../enums/nodeEnum.h"
NodeEnum::NodeType CreateNode::getNodeType( ) const {
	return NodeEnum::NodeType::Create;
}
