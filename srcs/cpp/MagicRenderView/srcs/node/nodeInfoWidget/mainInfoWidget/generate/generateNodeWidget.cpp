#include "generateNodeWidget.h"

#include <node/node/node.h>
bool GenerateNodeWidget::isNodeInfo( Node *check_node_ptr ) {
	return true;
}
bool GenerateNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	return true;
}
