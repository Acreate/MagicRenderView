#include "processNode.h"

#include "../../enums/nodeEnum.h"
NodeEnum::NodeType ProcessNode::getNodeType( ) const {
	return NodeEnum::NodeType::Process;
}
