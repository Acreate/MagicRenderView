#include "charCreateUnityNodeEditorWidget.h"

#include <director/varDirector.h>
#include <node/nodeStack/numberNodeStack/numberNode/create/bin/binCreateUnityNode.h>
#include <QLineEdit>

#include "../../charCreateUnityNode.h"
#include "charCreateUnityNodeEditorScrollArea.h"
void CharCreateUnityNodeEditorWidget::valueChange( QChar new_value ) {
	buffValue = new_value;
	qDebug( ) << buffValue;
}
CharCreateUnityNodeEditorWidget::CharCreateUnityNodeEditorWidget( CharCreateUnityNode *create_bin_node, QChar *bind_var_ptr ) : createBinNode( create_bin_node ), bindVarPtr( bind_var_ptr ) {
	if( bind_var_ptr == nullptr )
		return;
	binCreateUnityNodeScrollArea = new CharCreateUnityNodeEditorScrollArea( this, *bind_var_ptr );
	editorNodeInfoScrollArea = binCreateUnityNodeScrollArea;
	connect( binCreateUnityNodeScrollArea, &CharCreateUnityNodeEditorScrollArea::editingFinished_Signal, this, &CharCreateUnityNodeEditorWidget::valueChange );
}
CharCreateUnityNodeEditorWidget::~CharCreateUnityNodeEditorWidget( ) {
	if( binCreateUnityNodeScrollArea ) {
		callNodeReleaseInfoWidgetFunction( createBinNode );
		binCreateUnityNodeScrollArea = nullptr;
	}
}
bool CharCreateUnityNodeEditorWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	return true;
}
bool CharCreateUnityNodeEditorWidget::initNodeInfo( Node *check_node_ptr ) {
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
void CharCreateUnityNodeEditorWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
	*bindVarPtr = buffValue;
}
