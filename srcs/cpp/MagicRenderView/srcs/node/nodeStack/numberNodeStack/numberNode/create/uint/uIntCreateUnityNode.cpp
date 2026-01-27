#include "uIntCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/uIntOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "uintCreateNodeEditorWidget/unity/uIntCreateUnityNodeEditorWidget.h"

Def_Entity_NodeTypeName_Function( UIntCreateUnityNode, Node::tr( "创建/单元/无符号整数" ) );

UIntCreateUnityNode::UIntCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	editorWidget = nullptr;
	outputVarPtr = nullptr;
}
bool UIntCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool UIntCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool UIntCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}

bool UIntCreateUnityNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto nodeEditorWidget = qobject_cast< decltype(editorWidget) >( release_ptr );
	if( nodeEditorWidget == nullptr )
		return false;
	editorWidget = nodeEditorWidget;
	return true;
}
void UIntCreateUnityNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( release_ptr != editorWidget )
		return;
	editorWidget = nullptr;
}
NodeInfoWidget * UIntCreateUnityNode::getNodeInfoWidget( ) {
	if( editorWidget )
		return editorWidget;
	return new UIntCreateUnityNodeEditorWidget( this, outputVarPtr );
}
