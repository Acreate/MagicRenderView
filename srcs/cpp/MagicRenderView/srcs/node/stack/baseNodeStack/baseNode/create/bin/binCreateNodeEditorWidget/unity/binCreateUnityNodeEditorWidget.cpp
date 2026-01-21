#include "binCreateUnityNodeEditorWidget.h"

#include <director/varDirector.h>
#include <node/stack/baseNodeStack/baseNode/create/bin/binCreateUnityNode.h>
#include <node/stack/baseNodeStack/baseNode/create/bin/binCreateNodeEditorWidget/unity/binCreateUnityNodeEditorScrollArea.h>
#include <QLineEdit>
void BinCreateUnityNodeEditorWidget::valueChange( uint8_t new_value ) {
	buffValue = new_value;
}
BinCreateUnityNodeEditorWidget::BinCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node, uint8_t *bind_var_ptr ) : createBinNode( create_bin_node ), bindVarPtr( bind_var_ptr ) {
	if( bind_var_ptr == nullptr )
		return;
	binCreateUnityNodeScrollArea = new BinCreateUnityNodeEditorScrollArea( this, *bind_var_ptr );
	editorNodeInfoScrollArea = binCreateUnityNodeScrollArea;
	connect( binCreateUnityNodeScrollArea, &BinCreateUnityNodeEditorScrollArea::editingFinished_Signal, this, &BinCreateUnityNodeEditorWidget::valueChange );
}
BinCreateUnityNodeEditorWidget::~BinCreateUnityNodeEditorWidget( ) {
	if( binCreateUnityNodeScrollArea ) {
		callNodeReleaseInfoWidgetFunction( createBinNode );
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
	buffValue = *bindVarPtr;
	binCreateUnityNodeScrollArea->setCurrentVar( buffValue );
	return true;
}
void BinCreateUnityNodeEditorWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
	*bindVarPtr = buffValue;
}
