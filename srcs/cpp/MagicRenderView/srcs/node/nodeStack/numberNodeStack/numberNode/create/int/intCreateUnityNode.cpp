#include "intCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/intOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "intCreateNodeEditorWidget/unity/intCreateUnityNodeEditorWidget.h"

Def_Entity_NodeTypeName_Function( IntCreateUnityNode, Node::tr( "创建/单元/整数" ) );

IntCreateUnityNode::IntCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
	editorWidget = nullptr;
}
bool IntCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool IntCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool IntCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}

bool IntCreateUnityNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto nodeEditorWidget = qobject_cast< decltype(editorWidget) >( release_ptr );
	if( nodeEditorWidget == nullptr )
		return false;
	editorWidget = nodeEditorWidget;
	return true;
}
void IntCreateUnityNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( release_ptr != editorWidget )
		return;
	editorWidget = nullptr;
}
NodeInfoWidget * IntCreateUnityNode::getNodeEditorWidget( ) {
	if( editorWidget )
		return editorWidget;
	return new IntCreateUnityNodeEditorWidget( this, outputVarPtr );
}
