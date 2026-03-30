#include "NodeRunInfoDataEditor.h"
bool NodeRunInfoDataEditor::copyNodeRunInfoDataToThis( const NodeRunInfoData * const copy_target_ptr ) {
	return NodeRunInfoDataOnlyRead::copyNodeRunInfoDataToThis( copy_target_ptr );
}
void NodeRunInfoDataEditor::setBrforeRunDataTime( QDateTime *brfore_run_data_time ) {
	NodeRunInfoDataOnlyRead::setBrforeRunDataTime( brfore_run_data_time );
}
void NodeRunInfoDataEditor::setBuffNode( Node *buff_node ) {
	NodeRunInfoDataOnlyRead::setBuffNode( buff_node );
}
void NodeRunInfoDataEditor::setBuilderBeginList( const std::vector<Node *> &builder_begin_list ) {
	NodeRunInfoDataOnlyRead::setBuilderBeginList( builder_begin_list );
}
void NodeRunInfoDataEditor::setBuilderDataTime( QDateTime *builder_data_time ) {
	NodeRunInfoDataOnlyRead::setBuilderDataTime( builder_data_time );
}
void NodeRunInfoDataEditor::setBuilderNodeVector( const std::vector<Node *> &builder_node_vector ) {
	NodeRunInfoDataOnlyRead::setBuilderNodeVector( builder_node_vector );
}
void NodeRunInfoDataEditor::setBuilderReferenceSortVector( const std::vector<Node *> &builder_reference_sort_vector ) {
	NodeRunInfoDataOnlyRead::setBuilderReferenceSortVector( builder_reference_sort_vector );
}
void NodeRunInfoDataEditor::setCurrentFrame( size_t current_frame ) {
	NodeRunInfoDataOnlyRead::setCurrentFrame( current_frame );
}
void NodeRunInfoDataEditor::setCurrentNode( Node *current_node ) {
	NodeRunInfoDataOnlyRead::setCurrentNode( current_node );
}
void NodeRunInfoDataEditor::setCurrentRunDataTime( QDateTime *current_run_data_time ) {
	NodeRunInfoDataOnlyRead::setCurrentRunDataTime( current_run_data_time );
}
void NodeRunInfoDataEditor::setMaxFrame( size_t max_frame ) {
	NodeRunInfoDataOnlyRead::setMaxFrame( max_frame );
}
void NodeRunInfoDataEditor::setNextRunNodeTime( qint64 next_run_node_time ) {
	NodeRunInfoDataOnlyRead::setNextRunNodeTime( next_run_node_time );
}
void NodeRunInfoDataEditor::setOldNode( Node *old_node ) {
	NodeRunInfoDataOnlyRead::setOldNode( old_node );
}
void NodeRunInfoDataEditor::setReady( bool ready ) {
	NodeRunInfoDataOnlyRead::setReady( ready );
}
void NodeRunInfoDataEditor::setRunOverNodeVector( const std::vector<Node *> &run_over_node_vector ) {
	NodeRunInfoDataOnlyRead::setRunOverNodeVector( run_over_node_vector );
}
void NodeRunInfoDataEditor::setRunStop( bool run_stop ) {
	NodeRunInfoDataOnlyRead::setRunStop( run_stop );
}
