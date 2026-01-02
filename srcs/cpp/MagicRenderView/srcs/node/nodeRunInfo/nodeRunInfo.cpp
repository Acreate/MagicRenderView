#include "nodeRunInfo.h"

#include "../../srack/srackInfo.h"
NodeRunInfo::NodeRunInfo( QObject *parent ) : QObject( parent ), runArrayPtr( nullptr ), runArrayCount( 0 ), runArrayIndex( 0 ) {

}
NodeRunInfo::~NodeRunInfo( ) {
	clear( );
	emit release_signal( this, Create_SrackInfo( ) );
}
void NodeRunInfo::appendBegin( TRunBodyObj *benin_node_ref_link_info ) {
}
void NodeRunInfo::removeBegin( TRunBodyObj *benin_node_ref_link_info ) {
}
bool NodeRunInfo::hasNodeRefInRunVector( TRunBodyObj *check_node_ref ) {
	return false;
}
bool NodeRunInfo::builderRunInstance( ) {
	return true;
}
bool NodeRunInfo::runNextNode( ) {
	return false;
}
bool NodeRunInfo::runResidueNode( ) {
	return false;
}
void NodeRunInfo::clear( ) {
	beginNodeRefVector.clear( );
	runVector.clear( );
	runArrayPtr = nullptr;
	runArrayCount = 0;
	runArrayIndex = 0;
	emit clear_signal( this, Create_SrackInfo( ) );
}
