#include "nodeRunInfo.h"

#include <qdatetime.h>
#include <QThread>

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

#include "imp/NodeRunInfoDataEditor.h"

NodeRunInfo::NodeRunInfo( ) : QObject( ) {
	setNodeRunInfoData( new NodeRunInfoDataEditor );
	setNodeRunInfoDataImage( new NodeRunInfoDataEditor );
}
NodeRunInfo::~NodeRunInfo( ) {
	emit release_signal( this, Create_SrackInfo( ) );
	delete nodeRunInfoDataPtr;
	delete nodeRunInfoDataImagePtr;
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
NodeRunInfoDataEditor * NodeRunInfo::getNodeRunInfoDataEditor( ) const {
	return qobject_cast< NodeRunInfoDataEditor * >( nodeRunInfoDataPtr );
}
NodeRunInfoDataOnlyRead * NodeRunInfo::getNodeRunInfoDataOnlyRead( ) const {
	return qobject_cast< NodeRunInfoDataOnlyRead * >( nodeRunInfoDataPtr );
}
NodeRunInfoData * NodeRunInfo::getNodeRunInfoData( ) const {
	return nodeRunInfoDataPtr;
}
void NodeRunInfo::setNodeRunInfoData( NodeRunInfoData *new_node_run_info_data ) {
	nodeRunInfoDataPtr = new_node_run_info_data;
}
NodeRunInfoDataEditor * NodeRunInfo::getNodeRunInfoDataEditorImage( ) const {
	return qobject_cast< NodeRunInfoDataEditor * >( nodeRunInfoDataImagePtr );
}
NodeRunInfoDataOnlyRead * NodeRunInfo::getNodeRunInfoDataOnlyReadImage( ) const {
	return qobject_cast< NodeRunInfoDataOnlyRead * >( nodeRunInfoDataImagePtr );
}
NodeRunInfoData * NodeRunInfo::getNodeRunInfoDataImage( ) const {
	return nodeRunInfoDataImagePtr;
}
void NodeRunInfo::setNodeRunInfoDataImage( NodeRunInfoData *new_node_run_info_data_image ) {
	nodeRunInfoDataImagePtr = new_node_run_info_data_image;
}
void NodeRunInfo::appendBuilderNode( Node **append_node_array_ptr, const size_t &append_node_array_count ) {
	auto builderNodeCount = nodeRunInfoDataPtr->builderNodeVector.size( );
	size_t newSizet = append_node_array_count + builderNodeCount;
	nodeRunInfoDataPtr->builderNodeVector.resize( newSizet );
	auto builderNodeArrayPtr = nodeRunInfoDataPtr->builderNodeVector.data( );
	size_t builderNodeIndex;
	size_t index;
	for( index = 0; index < append_node_array_count; index += 1 )
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
		nodeRunInfoDataPtr->builderNodeVector.resize( builderNodeCount );
	builderNodeArrayPtr = nodeRunInfoDataPtr->builderNodeVector.data( );
	for( index = 0; index < builderNodeCount; index += 1 ) {
		// todo :
	}
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
	// todo :
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
			return;
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
	BuilderEnum::BuilderErrorType errorType = BuilderEnum::BuilderErrorType::BuilderSortError;
	resetBilderData( );
	if( sortFromBuilderNode( ) == false ) {
		printerDirector->info( tr( "编译节点排序参考失败" ), Create_SrackInfo( ) );
		resetBilderData( );
		return false;
	}

	size_t builderNodeIndex;
	size_t builderNodeCount;
	Node **builderNodeArrayPtr;

	builderNodeCount = nodeRunInfoDataPtr->builderReferenceSortVector.size( );
	builderNodeArrayPtr = nodeRunInfoDataPtr->builderReferenceSortVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 ) {
		builderNodeArrayPtr[ builderNodeIndex ]->setNodeStatusType( NodeEnum::NodeStatusType::None );
	}

	builderNodeCount = nodeRunInfoDataPtr->builderNodeVector.size( );
	builderNodeArrayPtr = nodeRunInfoDataPtr->builderNodeVector.data( );
	NodeRunLink *createNodeRunLink;
	errorType = BuilderEnum::BuilderErrorType::None;
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		switch( builderNodeArrayPtr[ builderNodeIndex ]->getNodeType( ) ) {
			case NodeEnum::NodeType::Point :

				break;
			case NodeEnum::NodeType::Create :

				break;

			case NodeEnum::NodeType::Function :

				break;
		}
	nodeRunInfoDataPtr->runStop = true;
	if( nodeRunInfoDataPtr->ready ) {
		if( this->nodeRunInfoDataImagePtr->copyNodeRunInfoDataToThis( this->nodeRunInfoDataPtr ) == false )
			nodeRunInfoDataPtr->ready = false;
	}
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
	size_t count = 0;
	if( count == 0 ) {
		nodeRunInfoDataPtr->ready = false;
		return false;
	}
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
void NodeRunInfo::resetData( ) {

	nodeRunInfoDataPtr->builderNodeVector.clear( );
	resetBilderData( );
}
void NodeRunInfo::resetBilderData( ) {
	nodeRunInfoDataPtr->ready = false;
	*nodeRunInfoDataPtr->currentRunDataTime = QDateTime::currentDateTime( );
	if( nodeRunInfoDataPtr->oldNode )
		nodeRunInfoDataPtr->oldNode->setNodeStatusType( NodeEnum::NodeStatusType::None );
	if( nodeRunInfoDataPtr->currentNode )
		nodeRunInfoDataPtr->currentNode->setNodeStatusType( NodeEnum::NodeStatusType::None );
	nodeRunInfoDataPtr->oldNode = nodeRunInfoDataPtr->currentNode = nullptr;
	nodeRunInfoDataPtr->currentFrame = 0;

	size_t builderNodeIndex;
	size_t builderNodeCount;
	Node **builderNodeArrayPtr;

	builderNodeCount = nodeRunInfoDataPtr->builderReferenceSortVector.size( );
	builderNodeArrayPtr = nodeRunInfoDataPtr->builderReferenceSortVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 ) {
		builderNodeArrayPtr[ builderNodeIndex ]->setNodeStatusType( NodeEnum::NodeStatusType::None );
	}
	nodeRunInfoDataPtr->builderReferenceSortVector.clear( );

}
bool NodeRunInfo::sortFromBuilderNode( ) {

	size_t count = nodeRunInfoDataPtr->builderBeginList.size( );
	if( count == 0 )
		return false;
	size_t index;

	std::vector< Node * > getRefNodeVector;
	auto data = nodeRunInfoDataPtr->builderBeginList.data( );
	for( index = 0; index < count; ++index ) // 获取依赖
		if( NodeRunLinkTools::getNodeRef( data[ index ], getRefNodeVector ) == false )
			return false;
	return NodeRunLinkTools::sortNodeRef( nodeRunInfoDataPtr->builderBeginList, getRefNodeVector, nodeRunInfoDataPtr->builderReferenceSortVector );
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
	nodeRunInfoDataPtr->builderBeginList.clear( );
	resetData( );
}
