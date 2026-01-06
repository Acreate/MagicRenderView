#include "endNode.h"

#include "beginNode.h"
bool EndNode::updateBeginData( BeginNode *begin_node_ptr ) {
	return begin_node_ptr->readNextBeginNodeData( );
}
