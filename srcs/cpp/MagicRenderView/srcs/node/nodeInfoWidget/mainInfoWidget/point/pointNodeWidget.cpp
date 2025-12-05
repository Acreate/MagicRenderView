#include "pointNodeWidget.h"

#include <node/node/node.h>
bool PointNodeWidget::isNodeInfo( Node *check_node_ptr ) {
	return true;
}
bool PointNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Point )
		return false;
	return true;
}
