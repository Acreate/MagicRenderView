#include "floatGenerateNodeWidget.h"

#include <enums/nodeEnum.h>
#include <node/node/node.h>

#include <node/node/imp/generateNodes/intGenerateNode.h>

#include "../../../../node/imp/generateNodes/floatGenerateNode.h"
#include "floatGenerateNodeEditor.h"
FloatGenerateNodeWidget::FloatGenerateNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = floatGenerateNodeEditor = new FloatGenerateNodeEditor( this );
	//setMinimumSize( 100, 200 );
}
bool FloatGenerateNodeWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	FloatGenerateNode *floatGenerateNodePtr = qobject_cast< FloatGenerateNode * >( check_node_ptr );
	if( floatGenerateNodePtr == nullptr )
		return false;
	return true;
}
bool FloatGenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	FloatGenerateNode *floatGenerateNodePtr = qobject_cast< FloatGenerateNode * >( check_node_ptr );
	if( floatGenerateNodePtr == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	floatGenerateNodeEditor->setBindGenerateVector( floatGenerateNodePtr->getGenerateVarPtr( ) );
	if( floatGenerateNodeEditor->updateGenerateItemInfo( ) == false )
		return false;
	return true;
}
void FloatGenerateNodeWidget::updateLayout( ) {
	NodeInfoWidget::updateLayout( );
}
void FloatGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void FloatGenerateNodeWidget::okButtonEvent( ) {
	floatGenerateNodeEditor->syncVarVector( );
	NodeInfoWidget::okButtonEvent( );
}
