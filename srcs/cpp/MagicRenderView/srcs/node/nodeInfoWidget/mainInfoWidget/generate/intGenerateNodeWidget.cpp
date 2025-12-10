#include "intGenerateNodeWidget.h"

#include "../../../node/imp/generateNodes/intGenerateNode.h"
#include "../../editNodeInfoScrollArea/generate/intGenerateNodeEditor.h"
IntGenerateNodeWidget::IntGenerateNodeWidget( MainWindow *parent ) : NodeInfoWidget( parent ) {
	intGenerateNodeEditor = new IntGenerateNodeEditor( this );
}
bool IntGenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	return true;
}
bool IntGenerateNodeWidget::isNodeTypeInfoWidget( Node *check_node_ptr ) const {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	IntGenerateNode *intGenerateNode = qobject_cast< IntGenerateNode * >( check_node_ptr );
	if( intGenerateNode == nullptr )
		return false;
	intGenerateNodeEditor->setBindGenerateVector( intGenerateNode->getGenerateVarPtr( ) );
	return true;
}
void IntGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void IntGenerateNodeWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
}
