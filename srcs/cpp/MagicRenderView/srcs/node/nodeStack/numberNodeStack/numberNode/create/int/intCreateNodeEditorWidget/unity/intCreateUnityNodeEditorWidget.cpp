#include "intCreateUnityNodeEditorWidget.h"

#include <director/varDirector.h>
#include <QLineEdit>

#include "../../intCreateUnityNode.h"
#include "intCreateUnityNodeEditorScrollArea.h"
void IntCreateUnityNodeEditorWidget::valueChange( int64_t new_value ) {
	buffValue = new_value;
}
IntCreateUnityNodeEditorWidget::IntCreateUnityNodeEditorWidget( IntCreateUnityNode *create_bin_node, int64_t *bind_var_ptr ) : createBinNode( create_bin_node ), bindVarPtr( bind_var_ptr ) {
	if( bind_var_ptr == nullptr )
		return;

	binCreateUnityNodeScrollArea = new IntCreateUnityNodeEditorScrollArea( this, *bind_var_ptr );
	editorNodeInfoScrollArea = binCreateUnityNodeScrollArea;
	connect( binCreateUnityNodeScrollArea, &IntCreateUnityNodeEditorScrollArea::editingFinished_Signal, this, &IntCreateUnityNodeEditorWidget::valueChange );
}
IntCreateUnityNodeEditorWidget::~IntCreateUnityNodeEditorWidget( ) {
	if( binCreateUnityNodeScrollArea ) {
		callNodeReleaseInfoWidgetFunction( createBinNode );
		binCreateUnityNodeScrollArea = nullptr;
	}
}
bool IntCreateUnityNodeEditorWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	return true;
}
bool IntCreateUnityNodeEditorWidget::initNodeInfo( Node *check_node_ptr ) {
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
void IntCreateUnityNodeEditorWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
	*bindVarPtr = buffValue;
}
