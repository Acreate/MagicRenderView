#include "generateNodeWidget.h"

#include <node/node/node.h>

#include "../../editNodeInfoScrollArea/generate/generateNodeEditor.h"

GenerateNodeWidget::GenerateNodeWidget( MainWindow *parent ) : NodeInfoWidget( parent ) {
	editorNodeInfoScrollArea = generateNodeEditor = new GenerateNodeEditor( this );
}
bool GenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	return true;
}
bool GenerateNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	return true;
}
