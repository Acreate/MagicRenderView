#include "startNodeWidget.h"

#include <node/node/node.h>

#include "../../../../node/imp/beginNodes/startNode.h"
#include "startNodeEditor.h"

StartNodeWidget::StartNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = startNodeEditor = new StartNodeEditor( this );
}

bool StartNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	auto nodeType = check_node_ptr->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Begin :
		case NodeEnum::NodeType::End :
			if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == true )
				return true;
	}
	return false;
}
bool StartNodeWidget::checkNodeValid( Node *check_node_ptr ) {
	auto nodeType = check_node_ptr->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Begin :
		case NodeEnum::NodeType::End :
			if( qobject_cast< StartNode * >( check_node_ptr ) != nullptr )
				return true;
	}
	return NodeInfoWidget::checkNodeValid( check_node_ptr );
}
void StartNodeWidget::updateLayout( ) {
	NodeInfoWidget::updateLayout( );
}
