#include "jumpNodeWidget.h"

#include <node/node/node.h>

#include "../../editNodeInfoScrollArea/jump/jumpNodeEditor.h"


JumpNodeWidget::JumpNodeWidget( MainWindow *parent ) : NodeInfoWidget( parent ) {
	editorNodeInfoScrollArea = jumpNodeEditor = new JumpNodeEditor( this );
}
bool JumpNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	return true;
}
bool JumpNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	NodeEnum::NodeType nodeType = check_node_ptr->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Point :
		case NodeEnum::NodeType::Jump :
			return true;
			break;
	}
	return false;
}
