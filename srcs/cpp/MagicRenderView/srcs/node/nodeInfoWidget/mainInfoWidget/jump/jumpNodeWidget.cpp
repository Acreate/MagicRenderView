#include "jumpNodeWidget.h"

#include <node/node/node.h>

bool JumpNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	return true;
}
bool JumpNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Jump )
		return false;
	return true;
}
