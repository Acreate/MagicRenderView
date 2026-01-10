#include "charGenerateNodeWidget.h"

#include <enums/nodeEnum.h>
#include <node/node/imp/generateNodes/uIntGenerateNode.h>
#include <node/node/node.h>

#include "../../../../node/imp/generateNodes/charGenerateNode.h"
#include "charGenerateNodeEditor.h"

CharGenerateNodeWidget::CharGenerateNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = charGenerateNodeEditor = new CharGenerateNodeEditor( this );
	//setMinimumSize( 100, 200 );
}
bool CharGenerateNodeWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	CharGenerateNode *charGenerateNodePtr = qobject_cast< CharGenerateNode * >( check_node_ptr );
	if( charGenerateNodePtr == nullptr )
		return false;
	return true;
}
bool CharGenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	CharGenerateNode *charGenerateNodePtr = qobject_cast< CharGenerateNode * >( check_node_ptr );
	if( charGenerateNodePtr == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	charGenerateNodeEditor->setBindGenerateVector( charGenerateNodePtr->getGenerateVarPtr( ) );
	if( charGenerateNodeEditor->updateGenerateItemInfo( ) == false )
		return false;
	return true;
}
void CharGenerateNodeWidget::updateLayout( ) {
	NodeInfoWidget::updateLayout( );
}
void CharGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void CharGenerateNodeWidget::okButtonEvent( ) {
	charGenerateNodeEditor->syncVarVector( );
	NodeInfoWidget::okButtonEvent( );
}
