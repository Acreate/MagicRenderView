#include "colorCreateUnityNodeEditorWidget.h"

#include <director/varDirector.h>
#include <QLineEdit>

#include "../../colorCreateUnityNode.h"
#include "colorCreateUnityNodeEditorScrollArea.h"
void ColorCreateUnityNodeEditorWidget::valueChange( QColor new_value ) {
	buffValue = new_value;
}
ColorCreateUnityNodeEditorWidget::ColorCreateUnityNodeEditorWidget( ColorCreateUnityNode *create_bin_node, QColor *bind_var_ptr ) : createBinNode( create_bin_node ), bindVarPtr( bind_var_ptr ) {
	if( bind_var_ptr == nullptr )
		return;
	binCreateUnityNodeScrollArea = new ColorCreateUnityNodeEditorScrollArea( this, *bind_var_ptr );
	editorNodeInfoScrollArea = binCreateUnityNodeScrollArea;
	connect( binCreateUnityNodeScrollArea, &ColorCreateUnityNodeEditorScrollArea::editingFinished_Signal, this, &ColorCreateUnityNodeEditorWidget::valueChange );
}
ColorCreateUnityNodeEditorWidget::~ColorCreateUnityNodeEditorWidget( ) {
	if( binCreateUnityNodeScrollArea ) {
		callNodeReleaseInfoWidgetFunction( createBinNode );
		delete binCreateUnityNodeScrollArea;
		binCreateUnityNodeScrollArea = nullptr;
		editorNodeInfoScrollArea = nullptr;
	}
}
bool ColorCreateUnityNodeEditorWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	return true;
}
bool ColorCreateUnityNodeEditorWidget::initNodeInfo( Node *check_node_ptr ) {
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
void ColorCreateUnityNodeEditorWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
	*bindVarPtr = buffValue;
}
