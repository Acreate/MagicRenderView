#include "floatCreateUnityNodeEditorWidget.h"


#include <director/varDirector.h>
#include <node/stack/numberNodeStack/numberNode/create/bin/binCreateUnityNode.h>
#include <node/stack/numberNodeStack/numberNode/create/bin/binCreateNodeEditorWidget/unity/binCreateUnityNodeEditorScrollArea.h>
#include <QLineEdit>

#include "floatCreateUnityNodeEditorScrollArea.h"
void FloatCreateUnityNodeEditorWidget::valueChange( uint8_t new_value ) {
	buffValue = new_value;
}
FloatCreateUnityNodeEditorWidget::FloatCreateUnityNodeEditorWidget( BinCreateUnityNode *create_bin_node, uint8_t *bind_var_ptr ) : createBinNode( create_bin_node ), bindVarPtr( bind_var_ptr ) {
	if( bind_var_ptr == nullptr )
		return;
	binCreateUnityNodeScrollArea = new FloatCreateUnityNodeEditorScrollArea( this, *bind_var_ptr );
	editorNodeInfoScrollArea = binCreateUnityNodeScrollArea;
	connect( binCreateUnityNodeScrollArea, &FloatCreateUnityNodeEditorScrollArea::editingFinished_Signal, this, &FloatCreateUnityNodeEditorWidget::valueChange );
}
FloatCreateUnityNodeEditorWidget::~FloatCreateUnityNodeEditorWidget( ) {
	if( binCreateUnityNodeScrollArea ) {
		callNodeReleaseInfoWidgetFunction( createBinNode );
		binCreateUnityNodeScrollArea = nullptr;
	}
}
bool FloatCreateUnityNodeEditorWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	return true;
}
bool FloatCreateUnityNodeEditorWidget::initNodeInfo( Node *check_node_ptr ) {
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
void FloatCreateUnityNodeEditorWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
	*bindVarPtr = buffValue;
}
