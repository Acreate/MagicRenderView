#include "NodeRunInfoEditor.h"
void NodeRunInfoEditor::setNodeRunInfoDataImage( NodeRunInfoData *new_node_run_info_data_image ) {
	NodeRunInfoOnlyRead::setNodeRunInfoDataImage( new_node_run_info_data_image );
}
void NodeRunInfoEditor::setNodeRunInfoData( NodeRunInfoData *new_node_run_info_data ) {
	NodeRunInfoOnlyRead::setNodeRunInfoData( new_node_run_info_data );
}

void NodeRunInfoEditor::appendBuilderNode( Node **append_node_array_ptr, const size_t &append_node_array_count ) {
	NodeRunInfoOnlyRead::appendBuilderNode( append_node_array_ptr, append_node_array_count );
}
void NodeRunInfoEditor::appendBuilderNode( Node *append_node_unity ) {
	NodeRunInfoOnlyRead::appendBuilderNode( append_node_unity );
}
bool NodeRunInfoEditor::builderRunInstance( ) {
	return NodeRunInfoOnlyRead::builderRunInstance( );
}

void NodeRunInfoEditor::removeBuilderNode( Node *append_node_unity ) {
	NodeRunInfoOnlyRead::removeBuilderNode( append_node_unity );
}
bool NodeRunInfoEditor::resetRunStartNode( ) {
	return NodeRunInfoOnlyRead::resetRunStartNode( );
}

bool NodeRunInfoEditor::toNextFrame( ) {
	return NodeRunInfoOnlyRead::toNextFrame( );
}
bool NodeRunInfoEditor::runNextNode( ) {
	return NodeRunInfoOnlyRead::runNextNode( );
}
bool NodeRunInfoEditor::runResidueNode( ) {
	return NodeRunInfoOnlyRead::runResidueNode( );
}
bool NodeRunInfoEditor::runStopNode( ) {
	return NodeRunInfoOnlyRead::runStopNode( );
}
bool NodeRunInfoEditor::runToNextFrame( ) {
	return NodeRunInfoOnlyRead::runToNextFrame( );
}
bool NodeRunInfoEditor::runToNode( const Node *target ) {
	return NodeRunInfoOnlyRead::runToNode( target );
}
