#include "uIntGenerateNodeWidget.h"
#include "uIntGenerateNodeEditor.h"

#include <enums/nodeEnum.h>
#include <node/node/imp/generateNodes/uIntGenerateNode.h>
#include <node/node/node.h>

UIntGenerateNodeWidget::UIntGenerateNodeWidget( ) : NodeInfoWidget( ) {
	editorNodeInfoScrollArea = uintGenerateNodeEditor = new UIntGenerateNodeEditor( this );
	//setMinimumSize( 100, 200 );
}
bool UIntGenerateNodeWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	UIntGenerateNode *uintGenerateNode = qobject_cast< UIntGenerateNode * >( check_node_ptr );
	if( uintGenerateNode == nullptr )
		return false;
	return true;
}
bool UIntGenerateNodeWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr->getNodeType( ) != NodeEnum::NodeType::Generate )
		return false;
	UIntGenerateNode *uintGenerateNode = qobject_cast< UIntGenerateNode * >( check_node_ptr );
	if( uintGenerateNode == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	uintGenerateNodeEditor->setBindGenerateVector( uintGenerateNode->getGenerateVarPtr( ) );
	if( uintGenerateNodeEditor->updateGenerateItemInfo( ) == false )
		return false;
	return true;
}
void UIntGenerateNodeWidget::updateLayout( ) {
	NodeInfoWidget::updateLayout( );
}
void UIntGenerateNodeWidget::cancelButtonEvent( ) {
	NodeInfoWidget::cancelButtonEvent( );
}
void UIntGenerateNodeWidget::okButtonEvent( ) {
	uintGenerateNodeEditor->syncVarVector( );
	NodeInfoWidget::okButtonEvent( );
}
