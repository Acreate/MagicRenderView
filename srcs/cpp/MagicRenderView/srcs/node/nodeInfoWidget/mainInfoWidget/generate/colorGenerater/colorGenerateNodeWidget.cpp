#include "colorGenerateNodeWidget.h"


#include <enums/nodeEnum.h>
#include <node/node/node.h>

#include "../../../../node/imp/generateNodes/colorGenerateNode.h"
#include "colorGenerateNodeEditor.h"

ColorGenerateNodeWidget::ColorGenerateNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = charGenerateNodeEditor = new ColorGenerateNodeEditor( this );
	//setMinimumSize( 100, 200 );
}
bool ColorGenerateNodeWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	ColorGenerateNode *charGenerateNodePtr = qobject_cast< ColorGenerateNode * >( check_node_ptr );
	if( charGenerateNodePtr == nullptr )
		return false;
	return true;
}
bool ColorGenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	ColorGenerateNode *charGenerateNodePtr = qobject_cast< ColorGenerateNode * >( check_node_ptr );
	if( charGenerateNodePtr == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	charGenerateNodeEditor->setBindGenerateVector( charGenerateNodePtr->getGenerateVarPtr( ) );
	if( charGenerateNodeEditor->updateGenerateItemInfo( ) == false )
		return false;
	return true;
}
void ColorGenerateNodeWidget::updateLayout( ) {
	NodeInfoWidget::updateLayout( );
}
void ColorGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void ColorGenerateNodeWidget::okButtonEvent( ) {
	charGenerateNodeEditor->syncVarVector( );
	NodeInfoWidget::okButtonEvent( );
}
