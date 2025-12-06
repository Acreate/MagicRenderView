#include "endNodeWidget.h"

#include <node/node/node.h>

#include "../../editNodeInfoScrollArea/editorNodeInfoScrollArea.h"
bool EndNodeWidget::initNodeInfo( Node *check_node_ptr ) {

	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	return true;
}
bool EndNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {

	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::End )
		return false;
	return true;
}
