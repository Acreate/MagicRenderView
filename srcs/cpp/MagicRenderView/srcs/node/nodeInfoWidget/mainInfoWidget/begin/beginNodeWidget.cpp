#include "beginNodeWidget.h"

#include <node/node/node.h>

#include <node/nodeInfoWidget/editNodeInfoScrollArea/begin/beginNodeEditor.h>

BeginNodeWidget::BeginNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = beginNodeEditor = new BeginNodeEditor( this );
}

bool BeginNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	auto nodeType = check_node_ptr->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Begin :
		case NodeEnum::NodeType::End :
			if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
				return false;
			return true;
	}
	return false;
}
