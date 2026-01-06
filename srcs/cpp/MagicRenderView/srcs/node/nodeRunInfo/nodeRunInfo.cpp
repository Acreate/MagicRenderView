#include "nodeRunInfo.h"

#include "../../app/application.h"
#include "../../director/nodeDirector.h"
#include "../../director/printerDirector.h"
#include "../../srack/srackInfo.h"
#include "../../tools/arrayTools.h"
#include "../node/node.h"

NodeRunInfo::NodeRunInfo( ) : QObject( ), builderNodeArrayPtr( nullptr ), builderNodeIndex( 0 ), builderNodeCount( 0 ), errorObj( nullptr ) {

}
NodeRunInfo::~NodeRunInfo( ) {
	clear( );
	emit release_signal( this, Create_SrackInfo( ) );
}
void NodeRunInfo::appendBuilderNode( TRunBodyObj **append_node_array_ptr, const size_t &append_node_array_count ) {
	size_t newSizet = append_node_array_count + builderNodeCount;
	builderNodeVector.resize( newSizet );
	builderNodeArrayPtr = builderNodeVector.data( );
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
	builderNodeArrayPtr = builderNodeVector.data( );
}
void NodeRunInfo::appendBuilderNode( TRunBodyObj *append_node_unity ) {
	if( append_node_unity == nullptr )
		return;
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == append_node_unity )
			return;
	builderNodeVector.emplace_back( append_node_unity );
	builderNodeArrayPtr = builderNodeVector.data( );
	builderNodeCount += 1;
}
void NodeRunInfo::removeBuilderNode( TRunBodyObj *append_node_unity ) {
	if( append_node_unity == nullptr )
		return;
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == append_node_unity ) {
			builderNodeVector.erase( builderNodeIndex + builderNodeVector.begin( ) );
			builderNodeArrayPtr = builderNodeVector.data( );
			builderNodeCount -= 1;
			return;
		}
}
bool NodeRunInfo::hasNodeRefInRunVector( TRunBodyObj *check_node_ref ) {
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == check_node_ref )
			return true;
	return false;
}
bool NodeRunInfo::builderRunInstance( ) {
	errorObj = nullptr;
	runNodeVector.clear( );
	runNodeArrayPtr = nullptr;
	runNodeCount = 0;
	runNodeIndex = 0;
	if( builderRunInstanceRef( ) == false )
		return false;
	runNodeArrayPtr = runNodeVector.data( );
	runNodeCount = runNodeVector.size( );
	runNodeIndex = 0;
	for( ; runNodeIndex < runNodeCount; ++runNodeIndex )
		if( runNodeArrayPtr[ runNodeIndex ]->readNodeRunData( ) == false ) {
			runNodeArrayPtr[ runNodeIndex ]->setNodeStyle( NodeEnum::NodeStyleType::Error );
			runNodeVector.clear( );
			runNodeArrayPtr = runNodeVector.data( );
			runNodeCount = runNodeVector.size( );
			runNodeIndex = 0;
			return false;
		} else
			runNodeArrayPtr[ runNodeIndex ]->setNodeStyle( NodeEnum::NodeStyleType::None );
	return runNodeCount != 0;
}
bool NodeRunInfo::builderRunInstanceRef( ) {
	if( builderNodeCount == 0 )
		return false;
	// 保存开始节点
	std::vector< Node * > beginNodeVector;
	// 保存结束节点
	std::vector< Node * > endNodeVector;
	// 保存流程节点
	std::vector< Node * > processNodeVector;
	Node *currentNode;
	size_t outputRefNodeCount;
	size_t outputRefNodeIndex;
	Node **outputRefNodeArray;
	std::vector< Node * > notRootNodeVector;
	NodeEnum::NodeType nodeType;
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 ) {
		currentNode = builderNodeArrayPtr[ builderNodeIndex ];
		nodeType = currentNode->getNodeType( );
		switch( nodeType ) {
			case NodeEnum::NodeType::InterFace :
				return false; // 未知节点
				break;
			case NodeEnum::NodeType::Begin :
				beginNodeVector.emplace_back( currentNode );
				break;
			case NodeEnum::NodeType::End :
				endNodeVector.emplace_back( currentNode );
				break;
			case NodeEnum::NodeType::Generate :
			case NodeEnum::NodeType::Jump :
			case NodeEnum::NodeType::Logic :
			case NodeEnum::NodeType::Process :
			case NodeEnum::NodeType::Cache :
			case NodeEnum::NodeType::Array :
			case NodeEnum::NodeType::Unity :
				outputRefNodeCount = currentNode->refOutputPortNode.size( );
				if( outputRefNodeCount == 0 ) {
					// 无根节点
					notRootNodeVector.emplace_back( currentNode );
					break;
				}
			case NodeEnum::NodeType::Point : // point 允许无根节点
				processNodeVector.emplace_back( currentNode );
				break;
		}

	}
	if( notRootNodeVector.size( ) != 0 ) {
		Application *instancePtr = Application::getInstancePtr( );
		auto arrayToString = instancePtr->getNodeDirector( )->nodeArrayToString( notRootNodeVector );
		QString form( "发现无根节点:\n\t%1" );
		instancePtr->getPrinterDirector( )->info( form.arg( arrayToString ), Create_SrackInfo( ) );
		return false;
	}
	if( beginNodeVector.size( ) == 0 ) {
		Application *instancePtr = Application::getInstancePtr( );
		auto arrayToString = instancePtr->getNodeDirector( )->nodeArrayToString( builderNodeArrayPtr, builderNodeCount );
		QString form( "未发现开始节点(NodeEnum::NodeType::Begin):\n\t%1" );
		instancePtr->getPrinterDirector( )->info( form.arg( arrayToString ), Create_SrackInfo( ) );
		return false;
	}
	// 流程节点大小
	size_t processSize = processNodeVector.size( );
	// 排序对象
	auto buffNodeArrayPtr = processNodeVector.data( );
	runNodeVector.resize( processSize );
	runNodeArrayPtr = runNodeVector.data( );
	runNodeIndex = 0;
	// 匹配依赖为 NodeEnum::NodeType::Begin 类型的节点
	for( builderNodeIndex = 0; builderNodeIndex < processSize; builderNodeIndex += 1 ) {
		currentNode = buffNodeArrayPtr[ builderNodeIndex ];
		outputRefNodeCount = currentNode->refOutputPortNode.size( );
		outputRefNodeArray = currentNode->refOutputPortNode.data( );
		for( outputRefNodeIndex = 0; outputRefNodeIndex < outputRefNodeCount; outputRefNodeIndex += 1 )
			if( outputRefNodeArray[ outputRefNodeIndex ]->getNodeType( ) != NodeEnum::NodeType::Begin )
				break;
		if( outputRefNodeIndex != outputRefNodeCount )
			continue;
		runNodeArrayPtr[ runNodeIndex ] = currentNode;
		runNodeIndex += 1;
		buffNodeArrayPtr[ builderNodeIndex ] = nullptr;
	}
	if( runNodeIndex == 0 ) {
		Application *instancePtr = Application::getInstancePtr( );
		auto arrayToString = instancePtr->getNodeDirector( )->nodeArrayToString( builderNodeArrayPtr, builderNodeCount );
		QString form( "未发现开始节点(NodeEnum::NodeType::Begin)依赖输出节点:\n\t%1" );
		instancePtr->getPrinterDirector( )->info( form.arg( arrayToString ), Create_SrackInfo( ) );
		return false;
	}
	ArrayTools::sortNullptr( buffNodeArrayPtr, processSize );
	for( builderNodeIndex = 0; builderNodeIndex < processSize; builderNodeIndex += 1 )
		if( buffNodeArrayPtr[ builderNodeIndex ] == nullptr )
			break; // 最大下标
	processSize = builderNodeIndex; // 重置大小

	// 开始正式排序内容
	do {
		for( builderNodeIndex = 0; builderNodeIndex < processSize; builderNodeIndex += 1 ) {
			currentNode = buffNodeArrayPtr[ builderNodeIndex ];
			outputRefNodeCount = currentNode->refOutputPortNode.size( );
			outputRefNodeArray = currentNode->refOutputPortNode.data( );
			for( outputRefNodeIndex = 0, runNodeCount = 0; outputRefNodeIndex < outputRefNodeCount; outputRefNodeIndex += 1, runNodeCount = 0 )
				if( ArrayTools::findIndex( buffNodeArrayPtr, runNodeIndex, outputRefNodeArray[ outputRefNodeIndex ], runNodeCount ) )
					break;
			if( outputRefNodeIndex != outputRefNodeCount )
				continue;
			runNodeArrayPtr[ runNodeIndex ] = currentNode;
			runNodeIndex += 1;
			buffNodeArrayPtr[ builderNodeIndex ] = nullptr;
		}
		ArrayTools::sortNullptr( buffNodeArrayPtr, processSize );
		for( builderNodeIndex = 0; builderNodeIndex < processSize; builderNodeIndex += 1 )
			if( buffNodeArrayPtr[ builderNodeIndex ] == nullptr )
				break; // 最大下标
		if( builderNodeIndex == 0 )
			break;// 不需要排序
		if( processSize == builderNodeIndex ) {
			Application *instancePtr = Application::getInstancePtr( );
			auto arrayToString = instancePtr->getNodeDirector( )->nodeArrayToString( buffNodeArrayPtr, processSize );
			QString form( "发现未知依赖节点:\n\t%1" );
			instancePtr->getPrinterDirector( )->info( form.arg( arrayToString ), Create_SrackInfo( ) );
			return false;
		}
		processSize = builderNodeIndex; // 重置大小
	} while( true );
	// 拷贝数据
	processNodeVector = runNodeVector;
	processSize = runNodeIndex;
	// 开始节点大小
	size_t beginSize = beginNodeVector.size( );
	// 结束节点大小
	size_t endSize = endNodeVector.size( );
	// 排序节点所有
	runNodeCount = beginSize + processSize + endSize;
	runNodeVector.resize( runNodeCount );
	runNodeArrayPtr = runNodeVector.data( );
	buffNodeArrayPtr = beginNodeVector.data( );
	// 添加开始列表
	for( builderNodeIndex = 0; builderNodeIndex < beginSize; builderNodeIndex += 1 )
		runNodeArrayPtr[ builderNodeIndex ] = buffNodeArrayPtr[ builderNodeIndex ];
	// 添加流程列表
	buffNodeArrayPtr = processNodeVector.data( );
	runNodeIndex = beginSize;
	for( builderNodeIndex = 0; builderNodeIndex < processSize; builderNodeIndex += 1 )
		runNodeArrayPtr[ builderNodeIndex + runNodeIndex ] = buffNodeArrayPtr[ builderNodeIndex ];
	// 添加结束列表
	buffNodeArrayPtr = endNodeVector.data( );
	runNodeIndex = runNodeIndex + processSize;
	for( builderNodeIndex = 0; builderNodeIndex < endSize; builderNodeIndex += 1 )
		runNodeArrayPtr[ builderNodeIndex + runNodeIndex ] = buffNodeArrayPtr[ builderNodeIndex ];
	return true;
}
bool NodeRunInfo::runNextNode( ) {
	if( runNodeCount == 0 || runNodeArrayPtr == nullptr )
		return false;
	if( runNodeCount == runNodeIndex )
		return true;
	std::vector< Node * > runCurrentNodeNeedNodeVector;
	if( runNodeIndex != 0 )
		runNodeArrayPtr[ runNodeIndex - 1 ]->setNodeStyle( NodeEnum::NodeStyleType::None );
	Node *currentRunNodePtr;
	currentRunNodePtr = runNodeArrayPtr[ runNodeIndex ];
	currentRunNodePtr->setNodeStyle( NodeEnum::NodeStyleType::Call_Function );
	if( currentRunNodePtr->fillInputPortCall( TODO, runCurrentNodeNeedNodeVector ) == false ) {
		Application *instancePtr = Application::getInstancePtr( );
		instancePtr->getPrinterDirector( )->info( tr( "运行 [%1]::fillInputPortCall(std::vector< Node * > &) 失败" ).arg( currentRunNodePtr->toQString( ) ), Create_SrackInfo( ) );
		currentRunNodePtr->setNodeStyle( NodeEnum::NodeStyleType::Error );
		return false;
	}
	size_t checkCount = runCurrentNodeNeedNodeVector.size( );
	size_t checkIndex = 0;

	auto checkNodeArray = runCurrentNodeNeedNodeVector.data( );
	size_t buffRunIndex;
	std::vector< Node * > errorNeedNodeVector;
	for( ; checkIndex < checkCount; checkIndex += 1 ) {
		for( buffRunIndex = 0; buffRunIndex < runNodeIndex; buffRunIndex += 1 )
			if( checkNodeArray[ checkIndex ] == runNodeArrayPtr[ buffRunIndex ] )
				break;
		if( buffRunIndex < runNodeIndex )
			continue;
		checkNodeArray[ checkIndex ]->setNodeStyle( NodeEnum::NodeStyleType::Advise );
		errorNeedNodeVector.emplace_back( checkNodeArray[ checkIndex ] );
	}
	// 如果存在错误列表，则输出
	if( errorNeedNodeVector.size( ) != 0 ) {
		Application *instancePtr = Application::getInstancePtr( );
		auto arrayToString = instancePtr->getNodeDirector( )->nodeArrayToString( errorNeedNodeVector );
		instancePtr->getPrinterDirector( )->info( tr( "运行[%1]失败，需要运行前置\n%2" ).arg( currentRunNodePtr->toQString( ) ).arg( arrayToString ), Create_SrackInfo( ) );
		currentRunNodePtr->setNodeStyle( NodeEnum::NodeStyleType::Error );
		return false;
	}
	if( currentRunNodePtr->fillNodeCall( TODO ) == false ) {
		Application *instancePtr = Application::getInstancePtr( );
		instancePtr->getPrinterDirector( )->info( tr( "运行 [%1]::fillNodeCall() 失败" ).arg( currentRunNodePtr->toQString( ) ), Create_SrackInfo( ) );
		currentRunNodePtr->setNodeStyle( NodeEnum::NodeStyleType::Error );
		return false;
	}
	std::vector< Node * > resultNextRunAdviseNodeVector;
	if( currentRunNodePtr->fillOutputPortCall( resultNextRunAdviseNodeVector, TODO ) == false ) {
		Application *instancePtr = Application::getInstancePtr( );
		instancePtr->getPrinterDirector( )->info( tr( "运行 [%1]::fillOutputPortCall(std::vector< Node * > &) 失败" ).arg( currentRunNodePtr->toQString( ) ), Create_SrackInfo( ) );
		currentRunNodePtr->setNodeStyle( NodeEnum::NodeStyleType::Error );
		return false;
	}
	runNodeIndex += 1;
	return true;
}
bool NodeRunInfo::runResidueNode( ) {
	if( runNodeCount == 0 || runNodeArrayPtr == nullptr )
		return false;
	if( runNodeCount == runNodeIndex )
		return true;
	isRunStop = false;
	do {
		if( runNextNode( ) == false )
			return false;
		if( isRunStop == true )
			break;
		if( runNodeCount == runNodeIndex )
			break;
	} while( true );
	return true;
}
bool NodeRunInfo::runStopNode( ) {
	isRunStop = true;
	return true;
}
void NodeRunInfo::clear( ) {
	builderNodeVector.clear( );
	builderNodeArrayPtr = nullptr;
	builderNodeCount = 0;
	builderNodeIndex = 0;
	runNodeVector.clear( );
	runNodeArrayPtr = nullptr;
	runNodeCount = 0;
	runNodeIndex = 0;
	errorObj = nullptr;
	emit clear_signal( this, Create_SrackInfo( ) );
}
