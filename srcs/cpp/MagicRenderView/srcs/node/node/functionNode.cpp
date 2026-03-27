#include "functionNode.h"

#include "../../enums/nodeEnum.h"
NodeEnum::NodeType FunctionNode::getNodeType( ) const {
	return NodeEnum::NodeType::Function;
}
