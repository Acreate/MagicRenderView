#include "nodeRunInfo.h"

#include <qdatetime.h>
#include <QThread>

#include "nodeRunInfoData.h"
#include "nodeRunInfoStack.h"

#include "../../app/application.h"

#include "../../director/printerDirector.h"

#include "../../enums/builderEnum.h"
#include "../../enums/nodeEnum.h"

#include "../../srack/srackInfo.h"
#include "../../tools/arrayTools.h"
#include "../../tools/vectorTools.h"
#include "../node/node.h"

#include "../../director/nodeDirector.h"

#include "../../tools/NodeRunLinkTools.h"

#include "imp/nodeRunInfoData/NodeRunInfoDataEditor.h"

NodeRunInfo::NodeRunInfo( ) : QObject( ) {
	nodeRunInfoDataPtr = new NodeRunInfoDataEditor;
	nodeRunInfoDataImagePtr = new NodeRunInfoDataEditor;
	nodeRunInfoStackPtr = new NodeRunInfoStack;
	nodeRunInfoStackPtr->pushCreateStackLast( *nodeRunInfoDataPtr );
}
NodeRunInfo::~NodeRunInfo( ) {
	emit release_signal( this, Create_SrackInfo( ) );
	delete nodeRunInfoDataPtr;
	delete nodeRunInfoDataImagePtr;
	delete nodeRunInfoStackPtr;
}
bool NodeRunInfo::hasBuilderNode( const Node *check_node_ptr ) {
	if( check_node_ptr == nullptr )
		return false;
	size_t builderNodeIndex;
	size_t builderNodeCount = nodeRunInfoDataPtr->builderNodeVector.size( );
	auto builderNodeArrayPtr = nodeRunInfoDataPtr->builderNodeVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == check_node_ptr )
			return true;
	return false;
}
NodeRunInfoData * NodeRunInfo::getNodeRunInfoData( ) const {
	return nodeRunInfoDataPtr;
}
void NodeRunInfo::setNodeRunInfoData( NodeRunInfoData *new_node_run_info_data ) {
	if( nodeRunInfoDataPtr )
		delete nodeRunInfoDataPtr;
	nodeRunInfoDataPtr = new_node_run_info_data;
}
NodeRunInfoData * NodeRunInfo::getNodeRunInfoDataImage( ) const {
	return nodeRunInfoDataImagePtr;
}
void NodeRunInfo::setNodeRunInfoDataImage( NodeRunInfoData *new_node_run_info_data_image ) {
	if( nodeRunInfoDataImagePtr )
		delete nodeRunInfoDataImagePtr;
	nodeRunInfoDataImagePtr = new_node_run_info_data_image;
}
void NodeRunInfo::appendBuilderNode( Node **append_node_array_ptr, const size_t &append_node_array_count ) {
	auto builderNodeCount = nodeRunInfoDataPtr->builderNodeVector.size( );
	size_t newSize = append_node_array_count + builderNodeCount;
	nodeRunInfoDataPtr->builderNodeVector.resize( newSize );
	auto builderNodeArrayPtr = nodeRunInfoDataPtr->builderNodeVector.data( );

	size_t appendIndex = 0;
	size_t findIndex = 0;
	for( ; appendIndex < append_node_array_count; ++appendIndex, findIndex = 0 )
		if( ArrayTools::findIndex( builderNodeArrayPtr, builderNodeCount, append_node_array_ptr[ appendIndex ], findIndex ) == false ) {
			builderNodeArrayPtr[ builderNodeCount ] = append_node_array_ptr[ appendIndex ];
			builderNodeCount += 1;
			if( append_node_array_ptr[ appendIndex ]->getNodeType( ) == NodeEnum::NodeType::Create )
				nodeRunInfoDataPtr->builderBeginVector.emplace_back( append_node_array_ptr[ appendIndex ] );
		}
	if( builderNodeCount != newSize )
		nodeRunInfoDataPtr->builderNodeVector.resize( builderNodeCount );
}
void NodeRunInfo::appendBuilderNode( Node *append_node_unity ) {
	if( append_node_unity == nullptr )
		return;
	size_t builderNodeIndex;
	size_t builderNodeCount = nodeRunInfoDataPtr->builderNodeVector.size( );
	auto builderNodeArrayPtr = nodeRunInfoDataPtr->builderNodeVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == append_node_unity )
			return;
	nodeRunInfoDataPtr->builderNodeVector.emplace_back( append_node_unity );
	if( append_node_unity->getNodeType( ) == NodeEnum::NodeType::Create )
		nodeRunInfoDataPtr->builderBeginVector.emplace_back( append_node_unity );
}
void NodeRunInfo::removeBuilderNode( Node *append_node_unity ) {
	if( append_node_unity == nullptr )
		return;
	size_t builderNodeIndex;
	size_t builderNodeCount = nodeRunInfoDataPtr->builderNodeVector.size( );
	auto builderNodeArrayPtr = nodeRunInfoDataPtr->builderNodeVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == append_node_unity ) {
			nodeRunInfoDataPtr->builderNodeVector.erase( builderNodeIndex + nodeRunInfoDataPtr->builderNodeVector.begin( ) );
			if( append_node_unity->getNodeType( ) != NodeEnum::NodeType::Create )
				return; // 不是 NodeEnum::NodeType::Create，则直接结束
			break; // 跳到删除 NodeEnum::NodeType::Create
		}
	builderNodeCount = nodeRunInfoDataPtr->builderBeginVector.size( );
	builderNodeArrayPtr = nodeRunInfoDataPtr->builderBeginVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == append_node_unity ) {
			nodeRunInfoDataPtr->builderBeginVector.erase( builderNodeIndex + nodeRunInfoDataPtr->builderBeginVector.begin( ) );
			break;
		}
}

bool NodeRunInfo::builderRunInstance( ) {
	if( nodeRunInfoDataPtr->runStop == false )
		return false;
	emit start_builder_signal( this );
	applicationPtr = Application::getInstancePtr( );
	if( applicationPtr == nullptr )
		return false;
	printerDirector = applicationPtr->getPrinterDirector( );
	if( printerDirector == nullptr )
		return false;
	nodeDirectorPtr = applicationPtr->getNodeDirector( );
	if( printerDirector == nullptr )
		return false;
	std::vector< Node * > getRefNodeVector;
	if( NodeRunLinkTools::fromBuilderNode( nodeRunInfoDataPtr->builderNodeVector, getRefNodeVector ) == false ) {
		printerDirector->info( tr( "编译节点参考失败" ), Create_SrackInfo( ) );
		return false;
	}

	// 重置节点状态
	size_t count = getRefNodeVector.size( );
	auto nodeDataPtr = getRefNodeVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		nodeDataPtr[ index ]->setNodeStatusType( NodeEnum::NodeStatusType::None );

	if( NodeRunLinkTools::sortNodeRef( nodeRunInfoDataPtr->builderBeginVector, getRefNodeVector, nodeRunInfoDataPtr->builderNodeVector ) == false ) {
		printerDirector->info( tr( "编译节点排序参考失败" ), Create_SrackInfo( ) );
		return false;
	}

	nodeRunInfoDataPtr->runStop = true;
	if( nodeRunInfoDataPtr->ready == false || this->nodeRunInfoDataImagePtr->copyNodeRunInfoDataToThis( this->nodeRunInfoDataPtr ) == false ) {
		nodeRunInfoDataPtr->ready = false;
		emit end_builder_signal( this );
		return nodeRunInfoDataPtr->ready;
	}

	// 输出-开始
	auto arrayToString = nodeDirectorPtr->nodeArrayToString( nodeRunInfoDataPtr->builderNodeVector );
	printerDirector->info( arrayToString, Create_SrackInfo( ) );
	// 输出-结束
	*nodeRunInfoDataPtr->builderDataTime = QDateTime::currentDateTime( );
	emit end_builder_signal( this );
	return nodeRunInfoDataPtr->ready;
}

bool NodeRunInfo::runNextNode( ) {
	if( nodeRunInfoDataPtr->ready == false || nodeRunInfoDataPtr->runStop == false )
		return false;
	nodeRunInfoDataPtr->runStop = false;
	emit auto_run_status_change_signal( this, nodeRunInfoDataPtr->runStop );

	nodeRunInfoDataPtr->runStop = true;
	emit auto_run_status_change_signal( this, nodeRunInfoDataPtr->runStop );
	return nodeRunInfoDataPtr->runStop;
}
bool NodeRunInfo::runResidueNode( ) {
	do {
		if( runToNextFrame( ) == false )
			break;
	} while( true );
	return true;
}
bool NodeRunInfo::runToNextFrame( ) {
	auto oldFrame = nodeRunInfoDataPtr->currentFrame;
	auto currentTime = QDateTime::currentDateTime( ).toMSecsSinceEpoch( );
	qint64 nextTime;
	qint64 sep;
	do {
		if( runNextNode( ) == false )
			break;
		if( oldFrame != currentTime )
			break;
		do {
			applicationPtr->processEvents( );
			nextTime = QDateTime::currentDateTime( ).toMSecsSinceEpoch( );
			sep = nextTime - currentTime;
			if( sep > nodeRunInfoDataPtr->nextRunNodeTime )
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
		if( nodeRunInfoDataPtr->currentNode == target )
			break;
		do {
			applicationPtr->processEvents( );
			nextTime = QDateTime::currentDateTime( ).toMSecsSinceEpoch( );
			sep = nextTime - currentTime;
			if( sep > nodeRunInfoDataPtr->nextRunNodeTime )
				break;
		} while( true );
		currentTime = nextTime;
	} while( true );
	return true;
}
bool NodeRunInfo::resetRunStartNode( ) {

	if( nodeRunInfoDataPtr->runStop == false || nodeRunInfoDataPtr->ready == false )
		return false;
	if( nodeRunInfoDataPtr->copyNodeRunInfoDataToThis( nodeRunInfoDataImagePtr ) == false ) {
		printerDirector->info( tr( "镜像重置数据失败" ), Create_SrackInfo( ) );
		nodeRunInfoDataPtr->ready = false;
		return false;
	}
	*nodeRunInfoDataPtr->currentRunDataTime = QDateTime::currentDateTime( );
	return true;
}
bool NodeRunInfo::runStopNode( ) {
	nodeRunInfoDataPtr->runStop = true;
	return true;
}

bool NodeRunInfo::toNextFrame( ) {
	auto oldFrame = nodeRunInfoDataPtr->currentFrame;
	if( nodeRunInfoDataPtr->copyNodeRunInfoDataToThis( this->nodeRunInfoDataImagePtr ) == false )
		return false;
	if( nodeRunInfoDataPtr->currentFrame == nodeRunInfoDataPtr->maxFrame )
		nodeRunInfoDataPtr->currentFrame = 0;
	else
		nodeRunInfoDataPtr->currentFrame = oldFrame + 1;
	return true;
}
void NodeRunInfo::clear( ) {
	emit clear_signal( this, Create_SrackInfo( ) );
	nodeRunInfoDataPtr->clear( );
}
