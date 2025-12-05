#include "jumpNodeWidget.h"

#include <node/node/node.h>

bool JumpNodeWidget::isNodeInfo( Node *check_node_ptr ) {
	return true;
}
bool JumpNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Jump )
		return false;
	return true;
}
