#include "intGenerateNodeWidget.h"

#include "../../../node/imp/generateNodes/intGenerateNode.h"
#include "../../bottomTool/bottomNodeInfoTool.h"
#include "../../editNodeInfoScrollArea/generate/intGenerateNodeEditor.h"
IntGenerateNodeWidget::IntGenerateNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = intGenerateNodeEditor = new IntGenerateNodeEditor( this );
	//setMinimumSize( 100, 200 );
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
void IntGenerateNodeWidget::updateLayout( ) {
	//NodeInfoWidget::updateLayout( );
	int currentWidth;
	int currentHeight;
	int buttonWidgetHeight;
	currentWidth = this->width( );
	if( currentWidth < 1 )
		return;
	currentHeight = this->height( );
	if( currentHeight < 1 )
		return;
	buttonWidgetHeight = buttonWidget->height( );

	intGenerateNodeEditor->move( 0, 0 );
	currentHeight -= buttonWidgetHeight;
	intGenerateNodeEditor->setFixedSize( currentWidth, currentHeight );
	buttonWidget->setFixedWidth( currentWidth );
	buttonWidget->move( 0, currentHeight );
}
void IntGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void IntGenerateNodeWidget::okButtonEvent( ) {
	intGenerateNodeEditor->syncVarVector( );
	NodeInfoWidget::okButtonEvent( );
}
