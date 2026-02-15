#include "nodeRunInfo.h"

#include <qdatetime.h>
#include <QThread>

#include "../../app/application.h"

#include "../../director/printerDirector.h"

#include "../../enums/nodeEnum.h"

#include "../../srack/srackInfo.h"
#include "../../tools/arrayTools.h"
#include "../../tools/vectorTools.h"
#include "../node/node.h"

#include "nodeRunLink/imp/callNodeRunLink.h"
#include "nodeRunLink/imp/createNodeRunLink.h"
#include "nodeRunLink/imp/pointNodeRunLink.h"
#include "nodeRunLink/nodeRunLink.h"

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
	if( runStop == false )
		return false;
	emit start_builder_signal( this );
	appinstancePtr = Application::getInstancePtr( );
	if( appinstancePtr == nullptr )
		return false;
	auto printerDirector = appinstancePtr->getPrinterDirector( );
	if( printerDirector == nullptr )
		return false;
	resetData( );

	size_t builderNodeIndex;
	size_t builderNodeCount = builderNodeVector.size( );
	auto builderNodeArrayPtr = builderNodeVector.data( );
	NodeRunLink *createNodeRunLink;
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		switch( builderNodeArrayPtr[ builderNodeIndex ]->getNodeType( ) ) {
			case NodeEnum::NodeType::Point :
				createNodeRunLink = new PointNodeRunLink( builderNodeArrayPtr[ builderNodeIndex ] );
				if( createNodeRunLink->builder( ) == false ) {
					delete createNodeRunLink;
					// 输出异常
					printerDirector->info( tr( "[%1] 初始化 [%2] 异常" ).arg( createNodeRunLink->metaObject( )->className( ) ).arg( builderNodeArrayPtr[ builderNodeIndex ]->toQString( ) ), Create_SrackInfo( ) );
				} else
					pointStack.emplace_back( createNodeRunLink );
				break;
			case NodeEnum::NodeType::Create :
				createNodeRunLink = new CreateNodeRunLink( builderNodeArrayPtr[ builderNodeIndex ] );
				if( createNodeRunLink->builder( ) == false ) {
					delete createNodeRunLink;
					// 输出异常
					printerDirector->info( tr( "[%1] 初始化 [%2] 异常" ).arg( createNodeRunLink->metaObject( )->className( ) ).arg( builderNodeArrayPtr[ builderNodeIndex ]->toQString( ) ), Create_SrackInfo( ) );
				} else
					createStack.emplace_back( createNodeRunLink );
				break;

			case NodeEnum::NodeType::Function :
				createNodeRunLink = new CallNodeRunLink( builderNodeArrayPtr[ builderNodeIndex ] );
				if( createNodeRunLink->builder( ) == false ) {
					delete createNodeRunLink;
					// 输出异常
					printerDirector->info( tr( "[%1] 初始化 [%2] 异常" ).arg( createNodeRunLink->metaObject( )->className( ) ).arg( builderNodeArrayPtr[ builderNodeIndex ]->toQString( ) ), Create_SrackInfo( ) );
				} else
					callStack.emplace_back( createNodeRunLink );
				break;

		}
	runStop = true;
	ready = createStack.size( ) > 0;
	if( ready == false )
		printerDirector->info( tr( "找不到匹配的起始节点（需要配置创建类型节点）" ), Create_SrackInfo( ) );
	emit end_builder_signal( this );
	return true;
}

bool NodeRunInfo::runNextNode( ) {

	if( ready == false || runStop == false )
		return false;
	runStop = false;
	emit auto_run_status_change_signal( this, runStop );
	NodeRunLink *nextNodeRunLink;
	Node *nextRunPtr;
	bool findNextNodePtr = getNextNodeRunLinkPtr( nextNodeRunLink );
	if( findNextNodePtr == true ) {
		nextRunPtr = nextNodeRunLink->getCurrentNode( );
		if( nextNodeRunLink->runRunNode( nextRunPtr, *currentRunDataTime, currentFrame ) == false ) {
			oldNode = currentNode;
			currentNode = nextRunPtr;
		} else {
			printerDirector->info( tr( "[%1] 运行 [%2] 节点异常" ).arg( nextNodeRunLink->metaObject( )->className( ) ).arg( nextRunPtr->toQString( ) ), Create_SrackInfo( ) );
		}
	} else {
		auto printerDirector = appinstancePtr->getPrinterDirector( );
		printerDirector->info( tr( "找不到匹配的下一个节点链接信息" ), Create_SrackInfo( ) );
	}
	runStop = true;
	emit auto_run_status_change_signal( this, runStop );
	return findNextNodePtr;
}
bool NodeRunInfo::runResidueNode( ) {
	do {
		if( runToNextFrame( ) == false )
			break;
	} while( true );
	return true;
}
bool NodeRunInfo::runToNextFrame( ) {
	auto oldFrame = currentFrame;
	auto currentTime = QDateTime::currentDateTime( ).toMSecsSinceEpoch( );
	qint64 nextTime;
	qint64 sep;
	do {
		if( runNextNode( ) == false )
			break;
		if( oldFrame != currentTime )
			break;
		do {
			appinstancePtr->processEvents( );
			nextTime = QDateTime::currentDateTime( ).toMSecsSinceEpoch( );
			sep = nextTime - currentTime;
			if( sep > msleepTime )
				break;
		} while( true );

		currentTime = nextTime;
	} while( true );
	return true;
}
bool NodeRunInfo::runToNode( const Node *target ) {
	auto currentTime = QDateTime::currentDateTime( ).toMSecsSinceEpoch( );
	qint64 nextTime;
	qint64 sep;
	do {
		if( runNextNode( ) == false )
			break;
		if( currentNode == target )
			break;
		do {
			appinstancePtr->processEvents( );
			nextTime = QDateTime::currentDateTime( ).toMSecsSinceEpoch( );
			sep = nextTime - currentTime;
			if( sep > msleepTime )
				break;
		} while( true );
		currentTime = nextTime;
	} while( true );
	return true;
}
bool NodeRunInfo::resetRunStartNode( ) {

	if( runStop == false || ready == false )
		return false;
	std::vector< NodeRunLink * >::iterator iterator;
	std::vector< NodeRunLink * >::iterator end;
	NodeRunLink *nodeRunLink;

	iterator = nodeRunLinkVector.begin( );
	end = nodeRunLinkVector.end( );
	for( ; iterator != end; ++iterator ) {
		nodeRunLink = *iterator;
		if( nodeRunLink->builder( ) )
			printerDirector->info( tr( "[%1] 重置失败" ).arg( nodeRunLink->metaObject( )->className( ) ), Create_SrackInfo( ) );
	}
	pointStack.clear( );
	callStack.clear( );
	createStack.clear( );
	*currentRunDataTime = QDateTime::currentDateTime( );
	oldNode = currentNode = nullptr;
	currentFrame = 0;
	return true;
}
bool NodeRunInfo::runStopNode( ) {
	runStop = true;
	return true;
}
void NodeRunInfo::resetData( ) {
	ready = false;
	*currentRunDataTime = QDateTime::currentDateTime( );
	oldNode = currentNode = nullptr;
	currentFrame = 0;
	builderNodeVector.clear( );
	createStack.clear( );
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
bool NodeRunInfo::getNextNodeRunLinkPtr( NodeRunLink *&result_next_node_ptr ) {
	return false;
}
void NodeRunInfo::clear( ) {
	emit clear_signal( this, Create_SrackInfo( ) );
	resetData( );
}
