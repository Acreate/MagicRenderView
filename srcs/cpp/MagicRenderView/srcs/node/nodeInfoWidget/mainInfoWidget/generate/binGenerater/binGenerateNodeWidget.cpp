#include "binGenerateNodeWidget.h"

#include <enums/nodeEnum.h>
#include <node/node/node.h>

#include "../../../../node/imp/generateNodes/binGenerateNode.h"
#include "binGenerateNodeEditor.h"

BinGenerateNodeWidget::BinGenerateNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = binGenerateNodeEditor = new BinGenerateNodeEditor( this );
	//setMinimumSize( 100, 200 );
}
bool BinGenerateNodeWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	BinGenerateNode *binGenerateNodePtr = qobject_cast< BinGenerateNode * >( check_node_ptr );
	if( binGenerateNodePtr == nullptr )
		return false;
	return true;
}
bool BinGenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	BinGenerateNode *binGenerateNodePtr = qobject_cast< BinGenerateNode * >( check_node_ptr );
	if( binGenerateNodePtr == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	binGenerateNodeEditor->setBindGenerateVector( binGenerateNodePtr->getGenerateVarPtr( ) );
	if( binGenerateNodeEditor->updateGenerateItemInfo( ) == false )
		return false;
	return true;
}
void BinGenerateNodeWidget::updateLayout( ) {
	NodeInfoWidget::updateLayout( );
}
void BinGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void BinGenerateNodeWidget::okButtonEvent( ) {
	binGenerateNodeEditor->syncVarVector( );
	NodeInfoWidget::okButtonEvent( );
}
