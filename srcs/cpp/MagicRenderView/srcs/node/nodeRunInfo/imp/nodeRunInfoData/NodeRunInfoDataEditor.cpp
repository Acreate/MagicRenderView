#include "NodeRunInfoDataEditor.h"
bool NodeRunInfoDataEditor::copyNodeRunInfoDataToThis( const NodeRunInfoData *const copy_target_ptr ) {
	return NodeRunInfoDataOnlyRead::copyNodeRunInfoDataToThis( copy_target_ptr );
}
bool NodeRunInfoDataEditor::copyNodeRunInfoDataToThis( const NodeRunInfoData &copy_target_instance ) {
	return NodeRunInfoDataOnlyRead::copyNodeRunInfoDataToThis( copy_target_instance );
}
void NodeRunInfoDataEditor::clear( ) {
	NodeRunInfoDataOnlyRead::clear( );
}
