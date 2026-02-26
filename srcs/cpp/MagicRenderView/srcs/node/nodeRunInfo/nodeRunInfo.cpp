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
	printerDirector = appinstancePtr->getPrinterDirector( );
	if( printerDirector == nullptr )
		return false;
	resetBilderData( );

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
					emit builder_error_signal( createNodeRunLink, BuilderEnum::BuilderErrorType::NodeBuilderError, builderNodeArrayPtr[ builderNodeIndex ] );
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
					emit builder_error_signal( createNodeRunLink, BuilderEnum::BuilderErrorType::NodeBuilderError, builderNodeArrayPtr[ builderNodeIndex ] );
					delete createNodeRunLink;
					break;
				}
				createVector.emplace_back( createNodeRunLink );
				emit builder_finish_signal( createNodeRunLink );
			{
				auto nodes = createNodeRunLink->getLinkNodeVector( );
				auto nodeArrayToString = appinstancePtr->getNodeDirector( )->nodeArrayToString( nodes );
				printerDirector->info( nodeArrayToString, Create_SrackInfo( ) );
			}
				break;

			case NodeEnum::NodeType::Function :
				if( stackHasStartNode( functionVector, builderNodeArrayPtr[ builderNodeIndex ] ) == true )
					break;
				createNodeRunLink = new CallNodeRunLink( builderNodeArrayPtr[ builderNodeIndex ] );
				if( createNodeRunLink->builder( ) == false ) {
					emit builder_error_signal( createNodeRunLink, BuilderEnum::BuilderErrorType::NodeBuilderError, builderNodeArrayPtr[ builderNodeIndex ] );
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
	} else {
		printerDirector->info( tr( "找不到匹配的起始节点（需要配置创建类型节点）" ), Create_SrackInfo( ) );
		emit builder_error_signal( nullptr, BuilderEnum::BuilderErrorType::None, nullptr );
	}
	emit end_builder_signal( this );
	return ready;
}

bool NodeRunInfo::runNextNode( ) {

	if( ready == false || runStop == false )
		return false;
	runStop = false;
	emit auto_run_status_change_signal( this, runStop );
	NodeRunLink *nextNodeRunLink;
	bool findNextNodePtr = getNextNodeRunLinkPtr( nextNodeRunLink, buffNode );
	if( findNextNodePtr == true ) {
		oldNode = currentNode;
		currentNode = buffNode;
		if( nextNodeRunLink->runRunNode( buffNode, *currentRunDataTime, currentFrame ) ) {
			std::vector< Node * > result;
			if( nextNodeRunLink->getNodeRunAdviseNodeVector( buffNode, result, *currentRunDataTime, currentFrame ) ) {
				// 删除堆栈中的信息
				if( nextNodeRunLink->isOver( ) )
					removeNodeRunLinkTarget( currentNode, nextNodeRunLink->getBeforeNode( )->getNodeType( ) );
				insertNodeRunLinkTarget( result );
			}
		} else
			printerDirector->info( tr( "[%1] 运行 [%2] 节点异常" ).arg( nextNodeRunLink->metaObject( )->className( ) ).arg( buffNode->toQString( ) ), Create_SrackInfo( ) );
	} else
		printerDirector->info( tr( "找不到匹配的下一个节点链接信息" ), Create_SrackInfo( ) );
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

	builderNodeVector.clear( );
	resetBilderData( );
}
void NodeRunInfo::resetBilderData( ) {
	ready = false;
	*currentRunDataTime = QDateTime::currentDateTime( );
	oldNode = currentNode = nullptr;
	currentFrame = 0;

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
bool NodeRunInfo::getNextNodeRunLinkPtr( NodeRunLink *&result_next_node_ptr, Node *result_node_ptr ) {
	// call 是否存在
	for( auto &checkTarget : functionStack ) {
		if( checkTarget->getNextRunNode( runOverNodeVector, result_node_ptr ) == false )
			continue;
		if( result_node_ptr == nullptr )
			continue;
		result_next_node_ptr = checkTarget;
		return true;
	}
	// create 是否存在
	for( auto &checkTarget : createStack ) {
		if( checkTarget->getNextRunNode( runOverNodeVector, result_node_ptr ) == false )
			continue;
		if( result_node_ptr == nullptr )
			continue;
		result_next_node_ptr = checkTarget;
		return true;
	}
	// if 是否存在
	for( auto &checkTarget : pointStack ) {
		if( checkTarget->getNextRunNode( runOverNodeVector, result_node_ptr ) == false )
			continue;
		if( result_node_ptr == nullptr )
			continue;
		result_next_node_ptr = checkTarget;
		return true;
	}
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
bool NodeRunInfo::removeNodeRunLinkTarget( Node *target_run_link ) {

	size_t vectorCount;
	NodeRunLink **vectorData;
	size_t vectorIndex;
	UATemStackType< NodeRunLink * >::iterator iterator;
	UATemStackType< NodeRunLink * >::iterator end;
	// call 堆栈吗?
	vectorCount = functionVector.size( );
	vectorData = functionVector.data( );
	vectorIndex = 0;
	for( ; vectorIndex < vectorCount; ++vectorIndex )
		if( vectorData[ vectorIndex ]->linkHasEndNode( target_run_link ) ) {
			iterator = functionStack.begin( );
			end = functionStack.end( );
			for( ; iterator != end; ++iterator )
				if( *iterator == vectorData[ vectorIndex ] ) {
					// 删除堆栈序列
					functionStack.erase( iterator );
					return true;
				}
			break;
		}
	if( vectorIndex == vectorCount ) {
		// point 堆栈吗?
		vectorCount = pointVector.size( );
		vectorData = pointVector.data( );
		vectorIndex = 0;
		for( ; vectorIndex < vectorCount; ++vectorIndex )
			if( vectorData[ vectorIndex ]->linkHasEndNode( target_run_link ) ) {
				iterator = pointStack.begin( );
				end = pointStack.end( );
				for( ; iterator != end; ++iterator )
					if( *iterator == vectorData[ vectorIndex ] ) {
						// 删除堆栈调用
						pointStack.erase( iterator );
						return true;
					}
				break;
			}
	}
	if( vectorIndex == vectorCount ) {
		// create 堆栈吗?
		vectorCount = createVector.size( );
		vectorData = createVector.data( );
		vectorIndex = 0;
		for( ; vectorIndex < vectorCount; ++vectorIndex )
			if( vectorData[ vectorIndex ]->linkHasEndNode( target_run_link ) ) {
				iterator = createStack.begin( );
				end = createStack.end( );
				for( ; iterator != end; ++iterator )
					if( *iterator == vectorData[ vectorIndex ] ) {
						// 删除堆栈调用
						createStack.erase( iterator );
						return true;
					}
			}
	}
	return false;
}
bool NodeRunInfo::insertNodeRunLinkTarget( const Node *const target_run_link ) {
	size_t vectorCount;
	NodeRunLink **vectorData;
	size_t vectorIndex;
	NodeEnum::NodeType nodeType;
	nodeType = target_run_link->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Function : {
			vectorCount = functionVector.size( );
			vectorData = functionVector.data( );
			vectorIndex = 0;
			for( ; vectorIndex < vectorCount; ++vectorIndex )
				if( vectorData[ vectorIndex ]->linkHasStartNode( target_run_link ) ) {
					if( vectorData[ vectorIndex ]->isOver( ) )
						rebuilderOverNodeRunLinkTarget( vectorData[ vectorIndex ] );
					functionStack.emplace_front( vectorData[ vectorIndex ] );
					break;
				}
			return true;
			break;
		}
		case NodeEnum::NodeType::Point : {
			vectorCount = pointVector.size( );
			vectorData = pointVector.data( );
			vectorIndex = 0;
			for( ; vectorIndex < vectorCount; ++vectorIndex )
				if( vectorData[ vectorIndex ]->linkHasStartNode( target_run_link ) ) {
					if( vectorData[ vectorIndex ]->isOver( ) )
						rebuilderOverNodeRunLinkTarget( vectorData[ vectorIndex ] );
					pointStack.emplace_back( vectorData[ vectorIndex ] );
					break;
				}
			return true;
			break;
		}
	}

	printerDirector->info( tr( "[ %1 ]节点匹配异常" ).arg( target_run_link->toQString( ) ),Create_SrackInfo( ) );
	return false;
}
bool NodeRunInfo::insertNodeRunLinkTarget( const std::vector< Node * > &target_run_link_vector ) {
	size_t count;
	const Node *const *data;
	size_t index;
	count = target_run_link_vector.size( );
	data = target_run_link_vector.data( );
	index = 0;
	for( ; index < count; ++index )
		if( insertNodeRunLinkTarget( data[ index ] ) == false )
			return false;

	return true;
}
bool NodeRunInfo::rebuilderOverNodeRunLinkTarget( NodeRunLink *rebuilder_target ) {
	NodeEnum::NodeType nodeType;
	size_t vectorCount;
	NodeRunLink **vectorData;
	size_t vectorIndex;
	Node *currentNode = rebuilder_target->getCurrentNode( );
	nodeType = currentNode->getNodeType( );
	switch( nodeType ) {
		case NodeEnum::NodeType::Call :
		case NodeEnum::NodeType::Function :
			vectorCount = functionVector.size( );
			vectorData = functionVector.data( );
			vectorIndex = 0;
			for( ; vectorIndex < vectorCount; ++vectorIndex )
				if( vectorData[ vectorIndex ] == rebuilder_target ) {
					if( rebuilder_target->builder( ) == false )
						break;
					filterOverNodeRunLinkVector( rebuilder_target->getLinkNodeVector( ) );
					return true;
				}
			break;
		case NodeEnum::NodeType::Point :
		case NodeEnum::NodeType::Jump :
			vectorCount = pointVector.size( );
			vectorData = pointVector.data( );
			vectorIndex = 0;
			for( ; vectorIndex < vectorCount; ++vectorIndex )
				if( vectorData[ vectorIndex ] == rebuilder_target ) {
					if( rebuilder_target->builder( ) == false )
						break;
					filterOverNodeRunLinkVector( rebuilder_target->getLinkNodeVector( ) );
					return true;
				}
			break;
	}
	printerDirector->info( tr( "[%1] 编译失败" ).arg( currentNode->toQString( ) ),Create_SrackInfo( ) );
	return false;
}
bool NodeRunInfo::removeNodeRunLinkTarget( Node *target_run_link, NodeEnum::NodeType node_type ) {
	size_t vectorCount;
	NodeRunLink **vectorData;
	size_t vectorIndex;
	UATemStackType< NodeRunLink * >::iterator iterator;
	UATemStackType< NodeRunLink * >::iterator end;
	switch( node_type ) {
		case NodeEnum::NodeType::Call : // call 堆栈吗?
		case NodeEnum::NodeType::Function :
			vectorCount = functionVector.size( );
			vectorData = functionVector.data( );
			vectorIndex = 0;
			for( ; vectorIndex < vectorCount; ++vectorIndex )
				if( vectorData[ vectorIndex ]->linkHasEndNode( target_run_link ) ) {
					iterator = functionStack.begin( );
					end = functionStack.end( );
					for( ; iterator != end; ++iterator )
						if( *iterator == vectorData[ vectorIndex ] ) {
							// 删除堆栈序列
							functionStack.erase( iterator );
							return true;
						}
					break;
				}
			break;
		case NodeEnum::NodeType::Point :
		case NodeEnum::NodeType::Jump :
			// point 堆栈吗?
			vectorCount = pointVector.size( );
			vectorData = pointVector.data( );
			vectorIndex = 0;
			for( ; vectorIndex < vectorCount; ++vectorIndex )
				if( vectorData[ vectorIndex ]->linkHasEndNode( target_run_link ) ) {
					iterator = pointStack.begin( );
					end = pointStack.end( );
					for( ; iterator != end; ++iterator )
						if( *iterator == vectorData[ vectorIndex ] ) {
							// 删除堆栈调用
							pointStack.erase( iterator );
							return true;
						}
					break;
				}
			break;
		case NodeEnum::NodeType::Foreach :
			break;
		case NodeEnum::NodeType::Logic :
			break;
		case NodeEnum::NodeType::Process :// create 堆栈吗?
		case NodeEnum::NodeType::Create :
			vectorCount = createVector.size( );
			vectorData = createVector.data( );
			vectorIndex = 0;
			for( ; vectorIndex < vectorCount; ++vectorIndex )
				if( vectorData[ vectorIndex ]->linkHasEndNode( target_run_link ) ) {
					iterator = createStack.begin( );
					end = createStack.end( );
					for( ; iterator != end; ++iterator )
						if( *iterator == vectorData[ vectorIndex ] ) {
							// 删除堆栈调用
							createStack.erase( iterator );
							return true;
						}
				}
			break;
	}

	return false;
}
size_t NodeRunInfo::filterOverNodeRunLinkVector( const std::vector< Node * > &filter_over_node_run_link_vector ) {
	size_t orgCount = runOverNodeVector.size( );
	std::vector< Node * > result;
	VectorTools::removeTarget( runOverNodeVector, filter_over_node_run_link_vector, result );
	runOverNodeVector = result;
	return orgCount - runOverNodeVector.size( );
}
void NodeRunInfo::clear( ) {
	emit clear_signal( this, Create_SrackInfo( ) );
	resetData( );
}
