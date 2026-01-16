#include "logicNode.h"

#include "../../enums/nodeEnum.h"
NodeEnum::NodeType LogicNode::getNodeType( ) const {
	return NodeEnum::NodeType::Logic;
}
