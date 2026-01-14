#include "nodeRunInfo.h"

#include <qdatetime.h>
#include <QThread>

#include "../../app/application.h"
#include "../../director/nodeDirector.h"
#include "../../director/printerDirector.h"
#include "../../srack/srackInfo.h"
#include "../../tools/arrayTools.h"
#include "../../tools/vectorTools.h"
#include "../node/node.h"

NodeRunInfo::NodeRunInfo( ) : QObject( ), builderDataTime( nullptr ), brforeRunDataTime( nullptr ), currentRunDataTime( nullptr ) {
	// 等待1秒执行下一个节点
	waiteNextTime = 1000;
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
	appinstancePtr = Application::getInstancePtr( );
	if( appinstancePtr == nullptr )
		return false;
	currentFrame = 0;
	currentRunPtr = nullptr;
	beginNodeVector.clear( );
	waiteRunNodeVector.clear( );
	overRunNodeVector.clear( );
	adviseNodeVector.clear( );
	if( builderRunInstanceRef( ) == false )
		return false;
	size_t runNodeCount;
	// 检测开始节点个数
	runNodeCount = beginNodeVector.size( );
	if( runNodeCount == 0 )
		return false;
	// todo : 初始化运行列表
	if( builderDataTime == nullptr )
		builderDataTime = new QDateTime( );
	*builderDataTime = QDateTime::currentDateTime( );
	if( brforeRunDataTime == nullptr )
		brforeRunDataTime = new QDateTime( );
	*brforeRunDataTime = *builderDataTime;
	if( currentRunDataTime == nullptr )
		currentRunDataTime = new QDateTime( );
	*currentRunDataTime = *builderDataTime;
	adviseNodeVector = beginNodeVector;
	return true;
}
bool NodeRunInfo::builderRunInstanceRef( ) {
	auto builderNodeCount = builderNodeVector.size( );
	if( builderNodeCount == 0 )
		return false;
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
			case NodeEnum::NodeType::Jump :
			case NodeEnum::NodeType::Logic :
			case NodeEnum::NodeType::Process :
				outputRefNodeCount = currentNode->otherNodeOutputPortRefThisNodeInputPortVector.size( );
				if( outputRefNodeCount == 0 ) {
					if( currentNode->inputPortVector.size( ) != 0 ) {
						// 无根节点
						notRootNodeVector.emplace_back( currentNode );
						break;
					}
					beginNodeVector.emplace_back( currentNode );
					break;
				}
			case NodeEnum::NodeType::Point : // point 允许无根节点
				processNodeVector.emplace_back( currentNode );
				break;
		}

	}
	if( beginNodeVector.size( ) == 0 ) {
		Application *instancePtr = Application::getInstancePtr( );
		auto arrayToString = instancePtr->getNodeDirector( )->nodeArrayToString( builderNodeArrayPtr, builderNodeCount );
		QString form( "未发现开始节点(NodeEnum::NodeType::Begin):\n\t%1" );
		instancePtr->getPrinterDirector( )->info( form.arg( arrayToString ), Create_SrackInfo( ) );
		return false;
	}
	if( notRootNodeVector.size( ) != 0 ) {
		Application *instancePtr = Application::getInstancePtr( );
		auto arrayToString = instancePtr->getNodeDirector( )->nodeArrayToString( notRootNodeVector );
		QString form( "发现无根节点:\n\t%1" );
		instancePtr->getPrinterDirector( )->info( form.arg( arrayToString ), Create_SrackInfo( ) );
		return false;
	}
	// 流程节点大小
	size_t processSize = processNodeVector.size( );
	// 排序对象
	auto buffNodeArrayPtr = processNodeVector.data( );
	std::vector< Node * > runNodeVector( processSize );
	auto runNodeArrayPtr = runNodeVector.data( );
	size_t runNodeIndex = 0;
	auto beginCount = beginNodeVector.size( );
	auto beginArray = beginNodeVector.data( );
	size_t beginFindResult;
	// 匹配依赖为 NodeEnum::NodeType::Begin 类型的节点
	for( builderNodeIndex = 0; builderNodeIndex < processSize; builderNodeIndex += 1 ) {
		currentNode = buffNodeArrayPtr[ builderNodeIndex ];
		outputRefNodeCount = currentNode->otherNodeOutputPortRefThisNodeInputPortVector.size( );
		outputRefNodeArray = currentNode->otherNodeOutputPortRefThisNodeInputPortVector.data( );
		for( outputRefNodeIndex = 0; outputRefNodeIndex < outputRefNodeCount; outputRefNodeIndex += 1 )
			if( beginFindResult = 0, ArrayTools::findIndex( beginArray, beginCount, outputRefNodeArray[ outputRefNodeIndex ], beginFindResult ) == false )
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
			outputRefNodeCount = currentNode->otherNodeOutputPortRefThisNodeInputPortVector.size( );
			outputRefNodeArray = currentNode->otherNodeOutputPortRefThisNodeInputPortVector.data( );
			outputRefNodeIndex = 0, runNodeCount = 0;
			for( ; outputRefNodeIndex < outputRefNodeCount; outputRefNodeIndex += 1, runNodeCount = 0 )
				if( ArrayTools::findIndex( runNodeArrayPtr, runNodeIndex, outputRefNodeArray[ outputRefNodeIndex ], runNodeCount ) == false )
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
bool NodeRunInfo::isNextRunNode( Node *check_next_node ) {
	Node **overNodeArrayPtr;
	size_t overNodeIndex;
	size_t overNodeCount;
	size_t needRunNodeIndex;
	Node *needNode;
	NodeEnum::NodeType needNodeType;
	std::vector< Node * > resultNeedNodeVector;
	size_t needRunNodeArratCount;
	Node **needRunNodeArrayPtr;
	std::vector< Node * > resultAdviseNodeVector;
	size_t adviseCount;
	Node **nodeArrayPtr;
	overNodeCount = overRunNodeVector.size( );

	if( check_next_node->fillInputPortCall( *builderDataTime, resultNeedNodeVector, currentFrame ) == false )
		return false; // 输入要求获取异常
	needRunNodeArratCount = resultNeedNodeVector.size( );
	if( needRunNodeArratCount == 0 )
		return true; // 不需要满足

	overNodeArrayPtr = overRunNodeVector.data( );
	needRunNodeArrayPtr = resultNeedNodeVector.data( );
	needRunNodeIndex = 0;
	// 该节点的输入节点需要全匹配已经运行的列表
	for( ; needRunNodeIndex < needRunNodeArratCount; needRunNodeIndex += 1 ) {
		needNode = needRunNodeArrayPtr[ needRunNodeIndex ];
		// 需求节点类型检测
		needNodeType = needNode->getNodeType( );
		// 如果需求是逻辑节点
		if( needNodeType == NodeEnum::NodeType::Logic ) {
			if( needNode->fillOutputPortCall( adviseNodeVector, *builderDataTime, currentFrame ) == false )
				return false; // 条件获取失败
			adviseCount = adviseNodeVector.size( );
			if( adviseCount == 0 )
				break; // 条件不存在该节点
			nodeArrayPtr = adviseNodeVector.data( );
			for( overNodeIndex = 0; overNodeIndex < adviseCount; overNodeIndex += 1 )
				if( check_next_node == nodeArrayPtr[ overNodeIndex ] )
					break; // 存在当前列表，则跳出
			if( overNodeIndex == adviseCount )
				return false; // 无法在条件当中匹配满足逻辑条件的节点
		}
		// 匹配已经运行列表
		for( overNodeIndex = 0; overNodeIndex < overNodeCount; overNodeIndex += 1 )
			if( needNode == overNodeArrayPtr[ overNodeIndex ] )
				break; // 存在当前列表，则跳出
		if( overNodeIndex == overNodeCount )
			return false; // 整个结束列表都已经遍历，还找不到完成
	}

	return true;
}
bool NodeRunInfo::findNextRunNode( Node *&result_run_node ) {
	// 查找上一个节点的建议运行列表
	Node **findNodeArrayPtr;
	size_t findNodeArrayIndex;
	size_t findNodeArrayCount;
	size_t thisInputRefNodeCount;
	Node **thisInputRefNodeArray;
	size_t thisInputRefNodeIndex;
	Node **waiteRunArray;
	size_t waiteRunCount;
	Node **overRunArray;
	size_t overRunCount;
	size_t findResultIndex;
	findNodeArrayCount = adviseNodeVector.size( );
	// 建议列表存在时，遍历建议列表，并且从中获取一个可运行节点
	if( findNodeArrayCount != 0 ) {
		findNodeArrayPtr = adviseNodeVector.data( );
		for( findNodeArrayIndex = 0; findNodeArrayIndex < findNodeArrayCount; findNodeArrayIndex += 1 )
			if( findNodeArrayPtr[ findNodeArrayIndex ] == nullptr )
				continue;
			else if( isNextRunNode( findNodeArrayPtr[ findNodeArrayIndex ] ) == true ) {
				result_run_node = findNodeArrayPtr[ findNodeArrayIndex ];
				// 建议列表的剩余元素填充到等待列表
				for( findNodeArrayIndex = 0; findNodeArrayIndex < findNodeArrayCount; findNodeArrayIndex += 1 )
					if( findNodeArrayPtr[ findNodeArrayIndex ] == nullptr )
						continue;
					else if( findNodeArrayPtr[ findNodeArrayIndex ] != result_run_node )
						waiteRunNodeVector.emplace_back( findNodeArrayPtr[ findNodeArrayIndex ] );
				return true;
			}
	}

	// 无法在建议列表当中查找运行节点，则匹配等待列表
	findNodeArrayCount = waiteRunNodeVector.size( );
	if( findNodeArrayCount ) {
		findNodeArrayPtr = waiteRunNodeVector.data( );
		for( findNodeArrayIndex = 0; findNodeArrayIndex < findNodeArrayCount; findNodeArrayIndex += 1 )
			if( isNextRunNode( findNodeArrayPtr[ findNodeArrayIndex ] ) == true == true ) {
				result_run_node = findNodeArrayPtr[ findNodeArrayIndex ];
				// 等待列表当中找到相应的节点时候
				waiteRunNodeVector.erase( waiteRunNodeVector.begin( ) + findNodeArrayIndex );
				return true;
			}
	}
	// 把 adviseNodeVector 序列当中的需求节点放置到 adviseNodeVector 当中，并且把旧的 adviseNodeVector 放置到 waiteRunNodeVector 序列当中
	findNodeArrayCount = adviseNodeVector.size( );
	// 建议列表存在时，遍历建议列表，并且从中获取一个可运行节点
	if( findNodeArrayCount != 0 ) {
		waiteRunNodeVector.append_range( adviseNodeVector );
		std::vector< Node * > buffVector;
		findNodeArrayPtr = adviseNodeVector.data( );
		for( findNodeArrayIndex = 0; findNodeArrayIndex < findNodeArrayCount; findNodeArrayIndex += 1 )
			if( findNodeArrayPtr[ findNodeArrayIndex ] == nullptr )
				continue;
			else {
				waiteRunArray = waiteRunNodeVector.data( );
				waiteRunCount = waiteRunNodeVector.size( );

				overRunArray = overRunNodeVector.data( );
				overRunCount = overRunNodeVector.size( );
				thisInputRefNodeCount = findNodeArrayPtr[ findNodeArrayIndex ]->otherNodeOutputPortRefThisNodeInputPortVector.size( );
				if( thisInputRefNodeCount ) {
					thisInputRefNodeArray = findNodeArrayPtr[ findNodeArrayIndex ]->otherNodeOutputPortRefThisNodeInputPortVector.data( );
					for( thisInputRefNodeIndex = 0; thisInputRefNodeIndex < thisInputRefNodeCount; ++thisInputRefNodeIndex ) {
						result_run_node = thisInputRefNodeArray[ thisInputRefNodeIndex ];
						findResultIndex = 0;
						if( ArrayTools::findIndex( waiteRunArray, waiteRunCount, result_run_node, findResultIndex ) == true )
							continue;
						findResultIndex = 0;
						if( ArrayTools::findIndex( overRunArray, overRunCount, result_run_node, findResultIndex ) == true )
							continue;
						buffVector.emplace_back( result_run_node );
					}
					continue;
				}
			}
		adviseNodeVector.clear( );
		VectorTools::removeRepeat( buffVector, adviseNodeVector );
		result_run_node = nullptr;
		return true;
	}
	// 全部节点已经运行完毕
	return false;
}
bool NodeRunInfo::runCurrentNode( Node *run_node ) {
	if( currentRunPtr )
		currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::None );
	currentRunPtr = run_node;
	currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::Current_Run );
	if( currentRunPtr->fillNodeCall( *builderDataTime, currentFrame ) == true )
		return true;

	Application *instancePtr;
	PrinterDirector *printerDirector;
	QString msg;
	QString nodeToString;

	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	msg = tr( "运行 [%1]::fillNodeCall() 失败" );
	nodeToString = currentRunPtr->toQString( );
	msg = msg.arg( nodeToString );
	printerDirector->info( msg, Create_SrackInfo( ) );
	currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::Error );
	return false;
}
bool NodeRunInfo::overRunNode( ) {
	currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::Old_Run );
	if( currentRunPtr->fillOutputPortCall( adviseNodeVector, *builderDataTime, currentFrame ) == true )
		return true;
	Application *instancePtr;
	PrinterDirector *printerDirector;
	QString msg;
	QString nodeToString;
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	msg = tr( "节点 [%1] 后调用处理失败" );
	nodeToString = currentRunPtr->toQString( );
	msg = msg.arg( nodeToString );
	printerDirector->info( msg, Create_SrackInfo( ) );
	currentRunPtr->setNodeStyle( NodeEnum::NodeStyleType::Error );
	return false;
}
bool NodeRunInfo::filterToAdviseVector( ) {
	size_t count;
	Node *currentNode;
	NodeEnum::NodeType nodeType;
	Node **adviseArrayPtr;
	Node **buffArrayPtr;
	size_t buffIndex;
	size_t adviseIndex;
	std::vector< Node * > *buff;
	count = adviseNodeVector.size( );
	if( count == 0 )
		return true;
	adviseArrayPtr = adviseNodeVector.data( );
	buff = new std::vector< Node * >( count );
	if( buff == nullptr )
		return false; // 内存不足
	buffArrayPtr = buff->data( );
	buffIndex = 0;
	adviseIndex = 0;
	for( ; adviseIndex < count; adviseIndex += 1 ) {
		currentNode = adviseArrayPtr[ adviseIndex ];
		buffArrayPtr[ buffIndex ] = currentNode;
		buffIndex += 1;
	}
	if( buffIndex != count )
		adviseNodeVector = *buff;
	delete buff;
	return true;
}
bool NodeRunInfo::runNextNode( ) {
	Node *currentRunPtr = nullptr;
	do
		if( findNextRunNode( currentRunPtr ) == false )
			return false;
	while( currentRunPtr == nullptr );
	if( runCurrentNode( currentRunPtr ) == false )
		return false;
	if( overRunNode( ) == false )
		return false;
	if( filterToAdviseVector( ) == false )
		return false;
	overRunNodeVector.emplace_back( currentRunPtr );
	return true;
}
bool NodeRunInfo::runResidueNode( ) {
	isRunStop = false;
	std::chrono::milliseconds milliseconds;
	long long count;
	do {
		if( runNextNode( ) == false )
			return false;
		if( isRunStop == true )
			break;
		do {
			appinstancePtr->processEvents( );
			*currentRunDataTime = QDateTime::currentDateTime( );
			milliseconds = *currentRunDataTime - *builderDataTime;
			count = milliseconds.count( );
			if( count > waiteNextTime )
				break;
			QThread::msleep( 10 );
		} while( true );
		*builderDataTime = *currentRunDataTime;
	} while( true );
	return true;
}
bool NodeRunInfo::resetRunStartNode( ) {
	// 检测开始节点个数
	size_t count = beginNodeVector.size( );
	if( count == 0 )
		return false;
	// todo : 重置数据
	currentFrame = 0;
	currentRunPtr = nullptr;
	// 清除已运行列表
	overRunNodeVector.clear( );
	// 赋予开始节点到建议运行序列
	adviseNodeVector = beginNodeVector;
	return true;
}
bool NodeRunInfo::runStopNode( ) {
	isRunStop = true;
	return true;
}
void NodeRunInfo::clear( ) {
	builderNodeVector.clear( );
	beginNodeVector.clear( );
	adviseNodeVector.clear( );
	overRunNodeVector.clear( );
	currentRunPtr = nullptr;
	currentFrame = 0;
	emit clear_signal( this, Create_SrackInfo( ) );
}
