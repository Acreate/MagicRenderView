#include "foreachNode.h"

#include "../../enums/nodeEnum.h"
NodeEnum::NodeType ForeachNode::getNodeType( ) const {
	return NodeEnum::NodeType::Foreach;
}
