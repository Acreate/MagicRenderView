#include "stringCreateUnityNodeEditorWidget.h"

#include <director/varDirector.h>
#include <node/nodeStack/numberNodeStack/numberNode/create/bin/binCreateUnityNode.h>
#include <node/nodeStack/numberNodeStack/numberNode/create/bin/binCreateNodeEditorWidget/unity/binCreateUnityNodeEditorScrollArea.h>
#include <QLineEdit>

#include "stringCreateUnityNodeEditorScrollArea.h"
void StringCreateUnityNodeEditorWidget::valueChange( uint8_t new_value ) {
	buffValue = new_value;
}
StringCreateUnityNodeEditorWidget::StringCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node, uint8_t *bind_var_ptr ) : createBinNode( create_bin_node ), bindVarPtr( bind_var_ptr ) {
	if( bind_var_ptr == nullptr )
		return;
	binCreateUnityNodeScrollArea = new StringCreateUnityNodeEditorScrollArea( this, *bind_var_ptr );
	editorNodeInfoScrollArea = binCreateUnityNodeScrollArea;
	connect( binCreateUnityNodeScrollArea, &StringCreateUnityNodeEditorScrollArea::editingFinished_Signal, this, &StringCreateUnityNodeEditorWidget::valueChange );
}
StringCreateUnityNodeEditorWidget::~StringCreateUnityNodeEditorWidget( ) {
	if( binCreateUnityNodeScrollArea ) {
		callNodeReleaseInfoWidgetFunction( createBinNode );
		binCreateUnityNodeScrollArea = nullptr;
	}
}
bool StringCreateUnityNodeEditorWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	return true;
}
bool StringCreateUnityNodeEditorWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	buffValue = *bindVarPtr;
	binCreateUnityNodeScrollArea->setCurrentVar( buffValue );
	return true;
}
void StringCreateUnityNodeEditorWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
	*bindVarPtr = buffValue;
}
