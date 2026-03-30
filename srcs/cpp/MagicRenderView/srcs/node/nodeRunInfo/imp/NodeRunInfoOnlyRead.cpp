#include "NodeRunInfoOnlyRead.h"
NodeRunInfoData * NodeRunInfoOnlyRead::getNodeRunInfoData( ) const {
	return NodeRunInfo::getNodeRunInfoData( );
}
NodeRunInfoDataEditor * NodeRunInfoOnlyRead::getNodeRunInfoDataEditor( ) const {
	return NodeRunInfo::getNodeRunInfoDataEditor( );
}
NodeRunInfoDataOnlyRead * NodeRunInfoOnlyRead::getNodeRunInfoDataOnlyRead( ) const {
	return NodeRunInfo::getNodeRunInfoDataOnlyRead( );
}
NodeRunInfoDataEditor * NodeRunInfoOnlyRead::getNodeRunInfoDataEditorImage( ) const {
	return NodeRunInfo::getNodeRunInfoDataEditorImage( );
}
NodeRunInfoData * NodeRunInfoOnlyRead::getNodeRunInfoDataImage( ) const {
	return NodeRunInfo::getNodeRunInfoDataImage( );
}
NodeRunInfoDataOnlyRead * NodeRunInfoOnlyRead::getNodeRunInfoDataOnlyReadImage( ) const {
	return NodeRunInfo::getNodeRunInfoDataOnlyReadImage( );
}
bool NodeRunInfoOnlyRead::hasBuilderNode( const Node *check_node_ptr ) {
	return NodeRunInfo::hasBuilderNode( check_node_ptr );
}
