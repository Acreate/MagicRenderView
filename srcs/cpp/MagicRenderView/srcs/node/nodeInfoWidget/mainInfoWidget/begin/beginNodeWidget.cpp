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
			if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == true )
				return true;
	}
	return false;
}
bool BeginNodeWidget::checkNodeValid( Node *check_node_ptr ) {
	auto nodeType = check_node_ptr->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Begin :
		case NodeEnum::NodeType::End :
			return true;
	}
	return NodeInfoWidget::checkNodeValid( check_node_ptr );
}
void BeginNodeWidget::updateLayout( ) {
	NodeInfoWidget::updateLayout( );
}
