#include "stringGenerateNodeWidget.h"

#include <enums/nodeEnum.h>
#include <node/node/imp/generateNodes/uIntGenerateNode.h>
#include <node/node/node.h>

#include "../../../../node/imp/generateNodes/stringGenerateNode.h"
#include "stringGenerateNodeEditor.h"

StringGenerateNodeWidget::StringGenerateNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = stringGenerateNodeEditor = new StringGenerateNodeEditor( this );
	//setMinimumSize( 100, 200 );
}
bool StringGenerateNodeWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	StringGenerateNode *uintGenerateNode = qobject_cast< StringGenerateNode * >( check_node_ptr );
	if( uintGenerateNode == nullptr )
		return false;
	return true;
}
bool StringGenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	StringGenerateNode *uintGenerateNode = qobject_cast< StringGenerateNode * >( check_node_ptr );
	if( uintGenerateNode == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	stringGenerateNodeEditor->setBindGenerateVector( uintGenerateNode->getGenerateVarPtr( ) );
	if( stringGenerateNodeEditor->updateGenerateItemInfo( ) == false )
		return false;
	return true;
}
void StringGenerateNodeWidget::updateLayout( ) {
	NodeInfoWidget::updateLayout( );
}
void StringGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void StringGenerateNodeWidget::okButtonEvent( ) {
	stringGenerateNodeEditor->syncVarVector( );
	NodeInfoWidget::okButtonEvent( );
}
