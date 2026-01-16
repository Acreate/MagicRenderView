#include "pointNode.h"

#include "../../enums/nodeEnum.h"
NodeEnum::NodeType PointNode::getNodeType( ) const {
	return NodeEnum::NodeType::Point;
}
