#include "binCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/binOutputPort.h>

#include "binCreateNodeEditorWidget/unity/binCreateUnityNodeEditorWidget.h"

BinCreateUnityNode::BinCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool BinCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool BinCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
void BinCreateUnityNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {

	if( release_ptr == editorWidget )
		return;
	editorWidget = nullptr;
}
NodeInfoWidget * BinCreateUnityNode::getNodeEditorWidget( ) {
	if( editorWidget )
		return editorWidget;
	editorWidget = new BinCreateUnityNodeEditorWidget( this );
	return editorWidget;
}
bool BinCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool BinCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
