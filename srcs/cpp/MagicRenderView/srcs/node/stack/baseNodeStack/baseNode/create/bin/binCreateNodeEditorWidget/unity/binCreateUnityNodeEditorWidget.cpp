#include "binCreateUnityNodeEditorWidget.h"

#include "../../binCreateUnityNode.h"
#include "binCreateUnityNodeEditorScrollArea.h"
BinCreateUnityNodeEditorWidget::BinCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node ) : createBinNode( create_bin_node ) {
	binCreateUnityNodeScrollArea = new BinCreateUnityNodeEditorScrollArea( this );
	editorNodeInfoScrollArea = binCreateUnityNodeScrollArea;
}
BinCreateUnityNodeEditorWidget::~BinCreateUnityNodeEditorWidget( ) {
	if( binCreateUnityNodeScrollArea ) {
		auto currentNode = binCreateUnityNodeScrollArea->getCurrentNode( );
		callNodeReleaseInfoWidgetFunction( currentNode );
		if( currentNode != createBinNode )
			callNodeReleaseInfoWidgetFunction( createBinNode );
		
		delete binCreateUnityNodeScrollArea;
		binCreateUnityNodeScrollArea = nullptr;
	}
}
bool BinCreateUnityNodeEditorWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	return true;
}
bool BinCreateUnityNodeEditorWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	return true;
}
