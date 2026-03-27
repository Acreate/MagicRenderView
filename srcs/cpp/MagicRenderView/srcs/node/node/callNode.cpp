#include "callNode.h"

#include "../../enums/nodeEnum.h"
NodeEnum::NodeType CallNode::getNodeType( ) const {
	return NodeEnum::NodeType::Call;
}
