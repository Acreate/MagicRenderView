#include "endNodeWidget.h"

#include <node/node/node.h>
bool EndNodeWidget::isNodeInfo( Node *check_node_ptr ) {
	return true;
}
bool EndNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {

	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::End )
		return false;
	return true;
}
