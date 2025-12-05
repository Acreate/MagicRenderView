#include "beginNodeWidget.h"

#include <node/node/node.h>

#include "../../editNodeInfoScrollArea/begin/beginNodeEditor.h"

BeginNodeWidget::BeginNodeWidget( MainWindow *parent ) : NodeInfoWidget( parent ) {
	editorNodeInfoScrollArea = new BeginNodeEditor( this );
}
bool BeginNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {

	auto nodeType = check_node_ptr->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Begin :
			return true;
	}
	return false;
}
bool BeginNodeWidget::isNodeInfo( Node *check_node_ptr ) {
	bool initNode = editorNodeInfoScrollArea->initNode( check_node_ptr );
	if( initNode == false )
		return false;
	return true;
}
void BeginNodeWidget::okButtonEvent( ) {
	hide( );
}
void BeginNodeWidget::cancelButtonEvent( ) {
	hide( );
}
