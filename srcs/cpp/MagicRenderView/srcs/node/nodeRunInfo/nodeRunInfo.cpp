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
	builderDataTime = new QDateTime;
	brforeRunDataTime = new QDateTime;
	currentRunDataTime = new QDateTime;
	maxFrame = 60;
	nextRunNodeTime = 10;
}
NodeRunInfo::~NodeRunInfo( ) {
	emit release_signal( this, Create_SrackInfo( ) );
	size_t count = nodeRunLinkVector.size( );
	size_t index;
	NodeRunLink **nodeRunLinkData;
	if( count ) {
		nodeRunLinkData = nodeRunLinkVector.data( );
		index = 0;
		for( ; index < count; ++index )
			delete nodeRunLinkData[ index ];
	}
	delete builderDataTime;
	delete brforeRunDataTime;
	delete currentRunDataTime;
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
				if( stackHasStartNode( pointVector, builderNodeArrayPtr[ builderNodeIndex ] ) == true )
					break;
				createNodeRunLink = new PointNodeRunLink( builderNodeArrayPtr[ builderNodeIndex ] );
				if( createNodeRunLink->builder( ) == false ) {
					emit builder_error_signal( createNodeRunLink );
					delete createNodeRunLink;
					break;
				}
				pointVector.emplace_back( createNodeRunLink );
				emit builder_finish_signal( createNodeRunLink );
				break;
			case NodeEnum::NodeType::Create :
				if( stackHasStartNode( createVector, builderNodeArrayPtr[ builderNodeIndex ] ) == true )
					break;
				createNodeRunLink = new CreateNodeRunLink( builderNodeArrayPtr[ builderNodeIndex ] );
				if( createNodeRunLink->builder( ) == false ) {
					emit builder_error_signal( createNodeRunLink );
					delete createNodeRunLink;
					break;
				}
				createVector.emplace_back( createNodeRunLink );
				emit builder_finish_signal( createNodeRunLink );
				break;

			case NodeEnum::NodeType::Function :
				if( stackHasStartNode( functionVector, builderNodeArrayPtr[ builderNodeIndex ] ) == true )
					break;
				createNodeRunLink = new CallNodeRunLink( builderNodeArrayPtr[ builderNodeIndex ] );
				if( createNodeRunLink->builder( ) == false ) {
					emit builder_error_signal( createNodeRunLink );
					delete createNodeRunLink;
					break;
				}
				functionVector.emplace_back( createNodeRunLink );
				emit builder_finish_signal( createNodeRunLink );
				break;
		}
	runStop = true;
	builderNodeCount = createVector.size( );
	ready = builderNodeCount > 0;
	if( ready ) {
		// 放入存储
		nodeRunLinkVector.append_range( createVector );
		nodeRunLinkVector.append_range( functionVector );
		nodeRunLinkVector.append_range( pointVector );
		// 初始化
		functionStack = UATemStackType< NodeRunLink * >( createVector.begin( ), createVector.end( ) );
	} else
		printerDirector->info( tr( "找不到匹配的起始节点（需要配置创建类型节点）" ), Create_SrackInfo( ) );
	emit end_builder_signal( this );
	return ready;
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
			std::vector< Node * > result;
			if( nextNodeRunLink->getNodeRunAdviseNodeVector( nextRunPtr, result, *currentRunDataTime, currentFrame ) ) {
				size_t count;
				Node **data;
				size_t index;
				size_t vectorCount;
				NodeRunLink **vectorData;
				size_t vectorIndex;
				NodeEnum::NodeType nodeType;
				UATemStackType< NodeRunLink * >::iterator iterator;
				UATemStackType< NodeRunLink * >::iterator end;
				// 删除堆栈中的信息

				if( nextNodeRunLink->isOver( ) ) {
					// 函数堆栈吗?
					vectorCount = functionVector.size( );
					vectorData = functionVector.data( );
					vectorIndex = 0;
					for( ; vectorIndex < vectorCount; ++vectorIndex )
						if( vectorData[ vectorIndex ]->linkHasEndNode( nextRunPtr ) ) {
							iterator = functionStack.begin( );
							end = functionStack.end( );
							for( ; iterator != end; ++iterator )
								if( *iterator == vectorData[ vectorIndex ] ) {
									// 删除堆栈序列
									functionStack.erase( iterator );
									// 重新编译
									vectorData[ vectorIndex ]->builder( );
									break;
								}
							break;
						}
					if( vectorIndex == vectorCount ) {
						// 点堆栈吗?
						vectorCount = pointVector.size( );
						vectorData = pointVector.data( );
						vectorIndex = 0;
						for( ; vectorIndex < vectorCount; ++vectorIndex )
							if( vectorData[ vectorIndex ]->linkHasEndNode( nextRunPtr ) ) {
								iterator = pointStack.begin( );
								end = pointStack.end( );
								for( ; iterator != end; ++iterator )
									if( *iterator == vectorData[ vectorIndex ] ) {
										// 删除堆栈调用
										pointStack.erase( iterator );
										// 重新编译
										vectorData[ vectorIndex ]->builder( );
										break;
									}
								break;
							}
					}
				}
				// todo : 判定下一个节点
				count = result.size( );
				data = result.data( );
				index = 0;
				for( ; index < count; ++index ) {
					nodeType = data[ index ]->getNodeType( );
					switch( nodeType ) {
						case NodeEnum::NodeType::Function : {
							vectorCount = functionVector.size( );
							vectorData = functionVector.data( );
							vectorIndex = 0;
							for( ; vectorIndex < vectorCount; ++vectorIndex )
								if( vectorData[ vectorIndex ]->linkHasStartNode( data[ index ] ) ) {
									functionStack.emplace_front( vectorData[ vectorIndex ] );
									break;
								}
							break;
						}
						case NodeEnum::NodeType::Point : {
							vectorCount = pointVector.size( );
							vectorData = pointVector.data( );
							vectorIndex = 0;
							for( ; vectorIndex < vectorCount; ++vectorIndex )
								if( vectorData[ vectorIndex ]->linkHasStartNode( data[ index ] ) ) {
									pointStack.emplace_back( vectorData[ vectorIndex ] );
									break;
								}
							break;
						}
					}
				}
			}
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
			if( sep > nextRunNodeTime )
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
			if( sep > nextRunNodeTime )
				break;
		} while( true );
		currentTime = nextTime;
	} while( true );
	return true;
}
bool NodeRunInfo::resetRunStartNode( ) {

	if( runStop == false || ready == false )
		return false;
	size_t count = nodeRunLinkVector.size( );
	if( count == 0 ) {
		ready = false;
		return false;
	}
	pointStack.clear( );
	functionStack.clear( );
	createStack.clear( );
	auto data = nodeRunLinkVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->builder( ) == false ) {
			printerDirector->info( tr( "[%1] 重置失败" ).arg( data[ index ]->metaObject( )->className( ) ), Create_SrackInfo( ) );
			ready = false;
			return false;
		}
	*currentRunDataTime = QDateTime::currentDateTime( );
	oldNode = currentNode = nullptr;
	currentFrame = 0;
	functionStack = UATemStackType< NodeRunLink * >( createVector.begin( ), createVector.end( ) );
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
	functionStack.clear( );

	createVector.clear( );
	pointVector.clear( );
	functionVector.clear( );

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
bool NodeRunInfo::updateNextNodeRunLinkPtr( NodeRunLink *update_next_node_ptr ) {
	if( update_next_node_ptr->isOver( ) == false )
		return true;
	return true;
}
bool NodeRunInfo::stackHasStartNode( const std::vector< NodeRunLink * > &check_vector, Node *check_node ) const {
	size_t count = check_vector.size( );
	auto data = check_vector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->linkHasStartNode( check_node ) == true )
			return true;
	return false;
}
void NodeRunInfo::clear( ) {
	emit clear_signal( this, Create_SrackInfo( ) );
	resetData( );
}
