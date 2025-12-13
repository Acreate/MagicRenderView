#include "nodeRunInfo.h"

#include "../../srack/srackInfo.h"
NodeRunInfo::NodeRunInfo( QObject *parent ) : QObject( parent ), runArrayPtr( nullptr ), runArrayCount( 0 ), runArrayIndex( 0 ) {

}
NodeRunInfo::~NodeRunInfo( ) {
	emit release_signal( this, Create_SrackInfo( ) );
}
void NodeRunInfo::appendBegin( NodeRefLinkInfo *benin_node_ref_link_info ) {
}
void NodeRunInfo::removeBegin( NodeRefLinkInfo *benin_node_ref_link_info ) {
}
bool NodeRunInfo::hasNodeRefInRunVector( NodeRefLinkInfo *check_node_ref ) {
	return false;
}
bool NodeRunInfo::builderRunInstance( ) {
	return false;
}
bool NodeRunInfo::runNextNode( ) {
	return false;
}
bool NodeRunInfo::runResidueNode( ) {
	return false;
}
