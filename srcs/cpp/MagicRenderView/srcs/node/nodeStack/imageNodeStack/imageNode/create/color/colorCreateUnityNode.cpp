#include "colorCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "colorCreateNodeEditorWidget/unity/colorCreateUnityNodeEditorWidget.h"

Def_Entity_NodeTypeName_Function( ColorCreateUnityNode, Node::tr( "创建/单元/颜色" ) );

NodeInfoWidget * ColorCreateUnityNode::getNodeInfoWidget( ) {
	if( editorWidget )
		return editorWidget;
	return new ColorCreateUnityNodeEditorWidget( this, outputVarPtr );
}
bool ColorCreateUnityNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto nodeEditorWidget = qobject_cast< decltype(editorWidget) >( release_ptr );
	if( nodeEditorWidget == nullptr )
		return false;
	editorWidget = nodeEditorWidget;
	return true;
}
void ColorCreateUnityNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( release_ptr != editorWidget )
		return;

	editorWidget = nullptr;
}
ColorCreateUnityNode::ColorCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
	editorWidget = nullptr;
}
bool ColorCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = QColor( 0, 0, 0, 255 );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ColorCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool ColorCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
