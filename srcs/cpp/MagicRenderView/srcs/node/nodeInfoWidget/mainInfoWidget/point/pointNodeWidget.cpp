#include "pointNodeWidget.h"

#include <node/node/node.h>

#include "../../editNodeInfoScrollArea/point/pointNodeEditor.h"
PointNodeWidget::PointNodeWidget( MainWindow *parent ) : NodeInfoWidget( parent ) {
	editorNodeInfoScrollArea = pointNodeEditor = new PointNodeEditor( this );
}
bool PointNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	return true;
}
bool PointNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Point )
		return false;
	return true;
}
