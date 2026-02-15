#include "floatCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/floatOutputPort.h>
#include <node/nodeTools/nodeTools.h>

#include "floatCreateNodeEditorWidget/unity/floatCreateUnityNodeEditorWidget.h"

Def_Entity_NodeTypeName_Function( FloatCreateUnityNode, Node::tr( "创建/单元/浮点" ) );

FloatCreateUnityNode::FloatCreateUnityNode( const QString &node_name ) : CreateNode( node_name ) {
	editorWidget = nullptr;
	outputVarPtr = nullptr;
}
bool FloatCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return CreateNode::initEx( parent );
}
bool FloatCreateUnityNode::updateLayout( ) {
	if( CreateNode::updateLayout( ) == false )
		return false;
	return true;
}
bool FloatCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool FloatCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}

bool FloatCreateUnityNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto nodeEditorWidget = qobject_cast< decltype(editorWidget) >( release_ptr );
	if( nodeEditorWidget == nullptr )
		return false;
	editorWidget = nodeEditorWidget;
	return true;
}
void FloatCreateUnityNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( release_ptr != editorWidget )
		return;
	editorWidget = nullptr;
}
NodeInfoWidget * FloatCreateUnityNode::getNodeInfoWidget( ) {
	if( editorWidget )
		return editorWidget;
	return new FloatCreateUnityNodeEditorWidget( this, outputVarPtr );
}
