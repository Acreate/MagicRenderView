#include "jumpNode.h"

#include "../../enums/nodeEnum.h"
NodeEnum::NodeType JumpNode::getNodeType( ) const {
	return NodeEnum::NodeType::Jump;
}
