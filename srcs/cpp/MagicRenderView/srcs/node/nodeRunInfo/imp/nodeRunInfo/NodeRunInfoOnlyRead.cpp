#include "NodeRunInfoOnlyRead.h"
NodeRunInfoData * NodeRunInfoOnlyRead::getNodeRunInfoData( ) const {
	return NodeRunInfo::getNodeRunInfoData( );
}
NodeRunInfoData * NodeRunInfoOnlyRead::getNodeRunInfoDataImage( ) const {
	return NodeRunInfo::getNodeRunInfoDataImage( );
}
bool NodeRunInfoOnlyRead::hasBuilderNode( const Node *check_node_ptr ) {
	return NodeRunInfo::hasBuilderNode( check_node_ptr );
}
