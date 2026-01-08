#include "jumpNodeWidget.h"

#include <node/node/node.h>

#include "../../editNodeInfoScrollArea/jump/jumpNodeEditor.h"

JumpNodeWidget::JumpNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = jumpNodeEditor = new JumpNodeEditor( this );
}
bool JumpNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	NodeEnum::NodeType nodeType = check_node_ptr->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Point :
		case NodeEnum::NodeType::Jump :
			if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
				return false;
			return true;
	}
	return false;
}
