#include "nodeRunInfo.h"

#include <qdatetime.h>
#include <QThread>

#include "nodeRunLink.h"

#include "../../app/application.h"
#include "../../director/nodeDirector.h"
#include "../../director/printerDirector.h"
#include "../../srack/srackInfo.h"
#include "../../tools/arrayTools.h"
#include "../../tools/vectorTools.h"
#include "../node/node.h"

NodeRunInfo::NodeRunInfo( ) : QObject( ), builderDataTime( nullptr ), brforeRunDataTime( nullptr ), currentRunDataTime( nullptr ) {
	// 等待1秒执行下一个节点
	waiteNextNodeTime = 10;
	maxFrame = 60;
	msleepTime = 10;
}
NodeRunInfo::~NodeRunInfo( ) {
	clear( );
	if( builderDataTime )
		delete builderDataTime;
	if( brforeRunDataTime )
		delete brforeRunDataTime;
	if( currentRunDataTime )
		delete currentRunDataTime;
	emit release_signal( this, Create_SrackInfo( ) );
}
bool NodeRunInfo::hasBuilderNode( const Node *check_node_ptr ) {
	if( check_node_ptr == nullptr )
		return false;
	size_t builderNodeIndex;
	size_t builderNodeCount = builderNodeVector.size( );
	auto builderNodeArrayPtr = builderNodeVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == check_node_ptr )
			return true;
	return false;
}
void NodeRunInfo::appendBuilderNode( Node **append_node_array_ptr, const size_t &append_node_array_count ) {
	auto builderNodeCount = builderNodeVector.size( );
	size_t newSizet = append_node_array_count + builderNodeCount;
	builderNodeVector.resize( newSizet );
	auto builderNodeArrayPtr = builderNodeVector.data( );
	size_t builderNodeIndex;
	for( size_t index = 0; index < append_node_array_count; index += 1 )
		if( append_node_array_ptr[ index ] != nullptr ) {
			for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
				if( builderNodeArrayPtr[ builderNodeIndex ] == append_node_array_ptr[ index ] )
					break;
			if( builderNodeIndex != builderNodeCount )
				continue;
			builderNodeArrayPtr[ builderNodeCount ] = append_node_array_ptr[ index ];
			builderNodeCount += 1;
		}
	if( newSizet != builderNodeCount )
		builderNodeVector.resize( builderNodeCount );
}
void NodeRunInfo::appendBuilderNode( Node *append_node_unity ) {
	if( append_node_unity == nullptr )
		return;
	size_t builderNodeIndex;
	size_t builderNodeCount = builderNodeVector.size( );
	auto builderNodeArrayPtr = builderNodeVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == append_node_unity )
			return;
	builderNodeVector.emplace_back( append_node_unity );
}
void NodeRunInfo::removeBuilderNode( Node *append_node_unity ) {
	if( append_node_unity == nullptr )
		return;
	size_t builderNodeIndex;
	size_t builderNodeCount = builderNodeVector.size( );
	auto builderNodeArrayPtr = builderNodeVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == append_node_unity ) {
			builderNodeVector.erase( builderNodeIndex + builderNodeVector.begin( ) );
			return;
		}
}

bool NodeRunInfo::builderRunInstance( ) {
	appinstancePtr = Application::getInstancePtr( );
	if( appinstancePtr == nullptr )
		return false;

	// todo : 编译节点
	return true;
}

bool NodeRunInfo::runNextNode( ) {

	// todo : 运行下一个节点
	return true;
}
bool NodeRunInfo::runResidueNode( ) {

	// todo : 运行剩余节点
	return true;
}
bool NodeRunInfo::runToNextFrame( ) {

	// todo : 运行到下一帧
	return true;
}
bool NodeRunInfo::runToNode( const Node *target ) {

	// todo : 运行到指定节点
	return true;
}
bool NodeRunInfo::resetRunStartNode( ) {
	// todo : 重置运行
	isRunStop = true;
	return true;
}
bool NodeRunInfo::runStopNode( ) {
	isRunStop = true;
	return true;
}
void NodeRunInfo::clear( ) {
	emit clear_signal( this, Create_SrackInfo( ) );
	builderNodeVector.clear( );
	processStack.clear( );
	pointStack.clear( );
	pointStack.clear( );
	size_t count = nodeRunLinkVector.size( );
	size_t index;
	NodeRunLink **nodeRunLinkData;
	if( count ) {
		nodeRunLinkData = nodeRunLinkVector.data( );
		index = 0;
		for( ; index < count; ++index )
			delete nodeRunLinkData[ index ];
		nodeRunLinkVector.clear( );
	}
}
