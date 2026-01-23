#include "boolCreateUnityNodeEditorWidget.h"

#include <director/varDirector.h>
#include <QLineEdit>

#include "../../boolCreateUnityNode.h"
#include "boolCreateUnityNodeEditorScrollArea.h"
void BoolCreateUnityNodeEditorWidget::valueChange( uint8_t new_value ) {
	buffValue = new_value;
}
BoolCreateUnityNodeEditorWidget::BoolCreateUnityNodeEditorWidget( BoolCreateUnityNode *create_bin_node, bool *bind_var_ptr ) : createBoolNode( create_bin_node ), bindVarPtr( bind_var_ptr ) {
	if( bind_var_ptr == nullptr )
		return;
	boolCreateUnityNodeEditorScrollArea = new BoolCreateUnityNodeEditorScrollArea( this, *bind_var_ptr );
	editorNodeInfoScrollArea = boolCreateUnityNodeEditorScrollArea;
	connect( boolCreateUnityNodeEditorScrollArea, &BoolCreateUnityNodeEditorScrollArea::editingFinished_Signal, this, &BoolCreateUnityNodeEditorWidget::valueChange );
}
BoolCreateUnityNodeEditorWidget::~BoolCreateUnityNodeEditorWidget( ) {
	if( boolCreateUnityNodeEditorScrollArea ) {
		callNodeReleaseInfoWidgetFunction( createBoolNode );
		delete boolCreateUnityNodeEditorScrollArea;
		boolCreateUnityNodeEditorScrollArea = nullptr;
		editorNodeInfoScrollArea = nullptr;
	}
}
bool BoolCreateUnityNodeEditorWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr != createBoolNode )
		return false;
	if( createBoolNode == nullptr )
		return false;
	return true;
}
bool BoolCreateUnityNodeEditorWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr != createBoolNode )
		return false;
	if( createBoolNode == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	buffValue = *bindVarPtr;
	boolCreateUnityNodeEditorScrollArea->setCurrentVar( buffValue );
	return true;
}
void BoolCreateUnityNodeEditorWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
	*bindVarPtr = buffValue;
}
