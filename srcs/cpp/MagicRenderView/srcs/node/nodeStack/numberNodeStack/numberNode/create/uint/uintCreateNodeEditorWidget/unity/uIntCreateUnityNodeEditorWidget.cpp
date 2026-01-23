#include "uIntCreateUnityNodeEditorWidget.h"

#include <director/varDirector.h>
#include <node/nodeStack/numberNodeStack/numberNode/create/bin/binCreateUnityNode.h>
#include <node/nodeStack/numberNodeStack/numberNode/create/bin/binCreateNodeEditorWidget/unity/binCreateUnityNodeEditorScrollArea.h>
#include <QLineEdit>

#include "../../uIntCreateUnityNode.h"
#include "uintCreateUnityNodeEditorScrollArea.h"
void UIntCreateUnityNodeEditorWidget::valueChange( uint64_t new_value ) {
	buffValue = new_value;
}
UIntCreateUnityNodeEditorWidget::UIntCreateUnityNodeEditorWidget( UIntCreateUnityNode *create_bin_node, uint64_t *bind_var_ptr ) : createBindNode( create_bin_node ), bindVarPtr( bind_var_ptr ) {
	if( bind_var_ptr == nullptr )
		return;

	binCreateUnityNodeScrollArea = new UIntCreateUnityNodeEditorScrollArea( this, *bind_var_ptr );
	editorNodeInfoScrollArea = binCreateUnityNodeScrollArea;
	connect( binCreateUnityNodeScrollArea, &UIntCreateUnityNodeEditorScrollArea::editingFinished_Signal, this, &UIntCreateUnityNodeEditorWidget::valueChange );
}
UIntCreateUnityNodeEditorWidget::~UIntCreateUnityNodeEditorWidget( ) {
	if( binCreateUnityNodeScrollArea ) {
		callNodeReleaseInfoWidgetFunction( createBindNode );
		binCreateUnityNodeScrollArea = nullptr;
	}
}
bool UIntCreateUnityNodeEditorWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr != createBindNode )
		return false;
	if( createBindNode == nullptr )
		return false;
	return true;
}
bool UIntCreateUnityNodeEditorWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr != createBindNode )
		return false;
	if( createBindNode == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	buffValue = *bindVarPtr;
	binCreateUnityNodeScrollArea->setCurrentVar( buffValue );
	return true;
}
void UIntCreateUnityNodeEditorWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
	*bindVarPtr = buffValue;
}
