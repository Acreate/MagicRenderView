#include "nodeRunInfo.h"

#include <qdatetime.h>

#include "../../app/application.h"
#include "../../director/nodeDirector.h"
#include "../../director/printerDirector.h"
#include "../../srack/srackInfo.h"
#include "../../tools/arrayTools.h"
#include "../node/node.h"

NodeRunInfo::NodeRunInfo( ) : QObject( ), builderDataTime( nullptr ) {

}
NodeRunInfo::~NodeRunInfo( ) {
	clear( );
	if( builderDataTime )
		delete builderDataTime;
	emit release_signal( this, Create_SrackInfo( ) );
}
void NodeRunInfo::appendBuilderNode( TRunBodyObj **append_node_array_ptr, const size_t &append_node_array_count ) {
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
void NodeRunInfo::appendBuilderNode( TRunBodyObj *append_node_unity ) {
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
void NodeRunInfo::removeBuilderNode( TRunBodyObj *append_node_unity ) {
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
bool NodeRunInfo::hasNodeRefInRunVector( TRunBodyObj *check_node_ref ) {
	size_t builderNodeIndex;
	size_t builderNodeCount = builderNodeVector.size( );
	auto builderNodeArrayPtr = builderNodeVector.data( );
	for( builderNodeIndex = 0; builderNodeIndex < builderNodeCount; builderNodeIndex += 1 )
		if( builderNodeArrayPtr[ builderNodeIndex ] == check_node_ref )
			return true;
	return false;
}
bool NodeRunInfo::builderRunInstance( ) {
	currentRunPtr = nullptr;
	runNodeVector.clear( );
	overRunNodeVector.clear( );
	if( builderRunInstanceRef( ) == false )
		return false;
	auto runNodeArrayPtr = runNodeVector.data( );
	auto runNodeCount = runNodeVector.size( );
	size_t runNodeIndex = 0;
	for( ; runNodeIndex < runNodeCount; ++runNodeIndex )
		if( runNodeArrayPtr[ runNodeIndex ]->readNodeRunData( ) == false ) {
			runNodeArrayPtr[ runNodeIndex ]->setNodeStyle( NodeEnum::NodeStyleType::Error );
			runNodeVector.clear( );
			return false;
		} else
			runNodeArrayPtr[ runNodeIndex ]->setNodeStyle( NodeEnum::NodeStyleType::None );
	if( runNodeCount == 0 )
		return false;
	if( builderDataTime == nullptr )
		builderDataTime = new QDateTime( );
	*builderDataTime = QDateTime::currentDateTime( );
	return true;
}
bool NodeRunInfo::builderRunInstanceRef( ) {
	auto builderNodeCount = builderNodeVector.size( );
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
	size_t builderNodeIndex;
	Node **outputRefNodeArray;
	std::vector< Node * > notRootNodeVector;
	NodeEnum::NodeType nodeType;
	auto builderNodeArrayPtr = builderNodeVector.data( );
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
	auto runNodeArrayPtr = runNodeVector.data( );
	size_t runNodeIndex = 0;
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
	size_t runNodeCount;
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
bool NodeRunInfo::findNextRunNode( Node *&result_run_node ) {
	// 查找上一个节点的建议运行列表
	if( result_run_node != nullptr ) {
		// 建议列表的剩余元素填充到等待列表

		return true;
	}
	// 无法在建议列表当中查找运行节点，则匹配等待列表
	if( result_run_node != nullptr ) {
		// 把当前节点剥离等待列表
		return true;
	}
	return false;
}
bool NodeRunInfo::runCurrentNode( Node *run_node ) {
	if( currentRunPtr )
		currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::None );
	currentRunPtr = run_node;
	currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::Current_Run );
	if( currentRunPtr->fillNodeCall( *builderDataTime ) == false )
		return false;
	return true;
}
bool NodeRunInfo::overRunNode( ) {
	currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::Old_Run );
	std::vector< Node * > resultNextRunAdviseNodeVector;
	if( currentRunPtr->fillOutputPortCall( resultNextRunAdviseNodeVector, *builderDataTime ) == false ) {
		Application *instancePtr = Application::getInstancePtr( );
		instancePtr->getPrinterDirector( )->info( tr( "运行 [%1]::fillOutputPortCall(std::vector< Node * > &) 失败" ).arg( currentRunPtr->toQString( ) ), Create_SrackInfo( ) );
		currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::Error );
		return false;
	}
	// 填充建议列表
	return false;
}
bool NodeRunInfo::runNextNode( ) {
	Node *currentRunPtr = nullptr;
	if( findNextRunNode( currentRunPtr ) == false ) {
		Application *instancePtr = Application::getInstancePtr( );
		auto nodeDirector = instancePtr->getNodeDirector( );
		auto arrayToString = nodeDirector->nodeArrayToString( waiteRunNodeVector );
		instancePtr->getPrinterDirector( )->info( tr( "无法匹配下一个节点:\n%2" ).arg( arrayToString ), Create_SrackInfo( ) );
		for( auto item : waiteRunNodeVector )
			item->setNodeStyle( NodeEnum::NodeStyleType::Error );
		return false;
	}
	if( runCurrentNode( currentRunPtr ) == false ) {
		Application *instancePtr = Application::getInstancePtr( );
		instancePtr->getPrinterDirector( )->info( tr( "运行 [%1]::fillNodeCall() 失败" ).arg( currentRunPtr->toQString( ) ), Create_SrackInfo( ) );
		currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::Error );
		return false;
	}
	if( overRunNode( ) == false ) {
		Application *instancePtr = Application::getInstancePtr( );
		instancePtr->getPrinterDirector( )->info( tr( "节点 [%1] 后调用处理失败" ).arg( currentRunPtr->toQString( ) ), Create_SrackInfo( ) );
		currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::Error );
		return false;
	}
	return true;
}
bool NodeRunInfo::runResidueNode( ) {
	isRunStop = false;
	do {
		if( runNextNode( ) == false )
			return false;
		if( isRunStop == true )
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
	runNodeVector.clear( );
	emit clear_signal( this, Create_SrackInfo( ) );
}
