#include "boolCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/nodeTools/nodeTools.h>

#include "../../../../../port/outputPort/unity/boolOutputPort.h"
#include "binCreateNodeEditorWidget/unity/boolCreateUnityNodeEditorWidget.h"

Def_Entity_NodeTypeName_Function( BoolCreateUnityNode, Node::tr("创建/单元/布尔" ) );

BoolCreateUnityNode::BoolCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	editorWidget = nullptr;
	outputVarPtr = nullptr;
}
bool BoolCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool BoolCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool BoolCreateUnityNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto converPtr = qobject_cast< decltype(editorWidget) >( release_ptr );
	if( converPtr == nullptr )
		return false;
	editorWidget = converPtr;
	return true;
}
void BoolCreateUnityNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( release_ptr != editorWidget )
		return;
	editorWidget = nullptr;
}
NodeInfoWidget * BoolCreateUnityNode::getNodeEditorWidget( ) {
	if( editorWidget )
		return editorWidget;

	return new BoolCreateUnityNodeEditorWidget( this, outputVarPtr );
}
bool BoolCreateUnityNode::readyNodeRunData( ) {
	*outputVarPtr = false;
	return true;
}
bool BoolCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
