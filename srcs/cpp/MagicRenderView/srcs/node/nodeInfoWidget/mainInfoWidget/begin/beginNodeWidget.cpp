#include "beginNodeWidget.h"

#include <node/node/node.h>

#include "../../editNodeInfoScrollArea/begin/beginNodeEditor.h"

BeginNodeWidget::BeginNodeWidget( MainWindow *parent ) : NodeInfoWidget( parent ) {
	editorNodeInfoScrollArea = beginNodeEditor = new BeginNodeEditor( this );
}
bool BeginNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {

	auto nodeType = check_node_ptr->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Begin :
			return true;
	}
	return false;
}
bool BeginNodeWidget::initNodeInfo( Node *check_node_ptr ) {

	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	return true;
}
void BeginNodeWidget::okButtonEvent( ) {
	hide( );
}
void BeginNodeWidget::cancelButtonEvent( ) {
	hide( );
}
