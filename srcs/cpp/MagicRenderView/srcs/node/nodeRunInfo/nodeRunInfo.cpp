#include "nodeRunInfo.h"

#include "../../srack/srackInfo.h"

NodeRunInfo::NodeRunInfo( QObject *parent ) : QObject( parent ), beginNodeArrayPtr( nullptr ), beginNodeIndex( 0 ), beginNodeCount( 0 ), errorObj( nullptr ) {

}
NodeRunInfo::~NodeRunInfo( ) {
	clear( );
	emit release_signal( this, Create_SrackInfo( ) );
}
void NodeRunInfo::appendBegin( TRunBodyObj *benin_node_ref_link_info ) {
	for( beginNodeIndex = 0; beginNodeIndex < beginNodeCount; beginNodeIndex += 1 )
		if( beginNodeArrayPtr[ beginNodeIndex ] == benin_node_ref_link_info )
			return;
	beginNodeVector.emplace_back( benin_node_ref_link_info );
	beginNodeArrayPtr = beginNodeVector.data( );
	beginNodeCount += 1;
}
void NodeRunInfo::removeBegin( TRunBodyObj *benin_node_ref_link_info ) {
	for( beginNodeIndex = 0; beginNodeIndex < beginNodeCount; beginNodeIndex += 1 )
		if( beginNodeArrayPtr[ beginNodeIndex ] == benin_node_ref_link_info ) {
			beginNodeVector.erase( beginNodeIndex + beginNodeVector.begin( ) );
			beginNodeArrayPtr = beginNodeVector.data( );
			beginNodeCount -= 1;
			return;
		}
}
bool NodeRunInfo::hasNodeRefInRunVector( TRunBodyObj *check_node_ref ) {
	for( beginNodeIndex = 0; beginNodeIndex < beginNodeCount; beginNodeIndex += 1 )
		if( beginNodeArrayPtr[ beginNodeIndex ] == check_node_ref )
			return true;
	return false;
}
bool NodeRunInfo::builderRunInstance( ) {
	errorObj = nullptr;
	runNodeVector.clear( );
	runNodeArrayPtr = nullptr;
	runNodeCount = 0;
	runNodeIndex = 0;
	return true;
}
bool NodeRunInfo::runNextNode( ) {
	return false;
}
bool NodeRunInfo::runResidueNode( ) {
	return false;
}
void NodeRunInfo::clear( ) {
	beginNodeVector.clear( );
	beginNodeArrayPtr = nullptr;
	beginNodeCount = 0;
	beginNodeIndex = 0;
	runNodeVector.clear( );
	runNodeArrayPtr = nullptr;
	runNodeCount = 0;
	runNodeIndex = 0;
	errorObj = nullptr;
	emit clear_signal( this, Create_SrackInfo( ) );
}
