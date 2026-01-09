#include "intGenerateNodeWidget.h"

#include "../../../node/imp/generateNodes/intGenerateNode.h"
#include "../../editNodeInfoScrollArea/generate/intGenerateNodeEditor.h"
IntGenerateNodeWidget::IntGenerateNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = intGenerateNodeEditor = new IntGenerateNodeEditor( this );
}
bool IntGenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	IntGenerateNode *intGenerateNode = qobject_cast< IntGenerateNode * >( check_node_ptr );
	if( intGenerateNode == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	intGenerateNodeEditor->setBindGenerateVector( intGenerateNode->getGenerateVarPtr( ) );
	if( intGenerateNodeEditor->updateGenerateItemInfo( ) == false )
		return false;
	return true;
}
void IntGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void IntGenerateNodeWidget::okButtonEvent( ) {
	intGenerateNodeEditor->syncVarVector( );
	NodeInfoWidget::okButtonEvent( );
}
