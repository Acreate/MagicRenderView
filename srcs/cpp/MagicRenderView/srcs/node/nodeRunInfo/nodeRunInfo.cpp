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
	maxFrame = 60;
	builderNodeArrayPtr = nullptr;
	builderNodeArrayCount = 0;
	overRunNodeArrayPtr = nullptr;
	overRunNodeArrayCount = 0;
	beginNodeArrayPtr = nullptr;
	beginNodeArrayCount = 0;
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
bool NodeRunInfo::isOverRunNode( Node *check_next_node ) {
	if( overRunNodeArrayCount == 0 )
		return false;
	size_t index;
	for( index = 0; index < overRunNodeArrayCount; ++index )
		if( overRunNodeArrayPtr[ index ] == check_next_node )
			return true;
	return false;
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
	overRunNodeArrayCount = 0;
	overRunNodeArrayPtr = nullptr;
	beginNodeArrayCount = 0;
	beginNodeArrayPtr = nullptr;
	beginNodeVector.clear( );
	waiteRunNodeVector.clear( );
	overRunNodeVector.clear( );
	adviseNodeVector.clear( );
	if( builderRunInstanceRef( ) == false )
		return false;
	// 检测开始节点个数
	beginNodeArrayCount = beginNodeVector.size( );
	if( beginNodeArrayCount == 0 )
		return false;
	beginNodeArrayPtr = beginNodeVector.data( );

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
	std::vector< std::pair< Node *, std::pair< std::vector< Node * >, std::vector< Node * > > > > erroNode;
	std::vector< Node * > erroRefInputNode;
	std::vector< Node * > erroRefOutputNode;
	std::vector< Node * > erroReadNode;
	size_t builderIndex;
	size_t findNodeIndex;
	size_t refCount;
	size_t refIndex;
	Node **refArrayPtr;
	NodeEnum::NodeType nodeType;
	std::pair< Node *, std::pair< std::vector< Node * >, std::vector< Node * > > > *errorMapArray;
	QString nodeTypeName;
	QStringList errorMsgList;
	QString appendErrorMsg;
	QString errorNodeMsgFormat;
	QString errorRefInMsgFormat;
	QString errorRefOutMsgFormat;
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	builderNodeArrayCount = builderNodeVector.size( );
	if( builderNodeArrayCount == 0 )
		return false;
	builderNodeArrayPtr = builderNodeVector.data( );
	for( builderIndex = 0; builderIndex < builderNodeArrayCount; ++builderIndex ) {
		erroRefInputNode.clear( );
		erroRefInputNode.clear( );
		builderNodeArrayPtr[ builderIndex ]->setNodeStyle( NodeEnum::NodeStyleType::None );
		if( builderNodeArrayPtr[ builderIndex ]->readyNodeRunData( ) == false ) {
			erroReadNode.emplace_back( builderNodeArrayPtr[ builderIndex ] );
			continue;
		}
		refCount = builderNodeArrayPtr[ builderIndex ]->thisNodeOutputPortRefOtherNodeInputPortVector.size( );
		if( refCount != 0 ) {
			refArrayPtr = builderNodeArrayPtr[ builderIndex ]->thisNodeOutputPortRefOtherNodeInputPortVector.data( );
			for( refIndex = 0, findNodeIndex = 0; refIndex < refCount; ++refIndex, findNodeIndex = 0 )
				if( ArrayTools::findIndex( builderNodeArrayPtr, builderNodeArrayCount, refArrayPtr[ refIndex ], findNodeIndex ) == false )
					erroRefOutputNode.emplace_back( refArrayPtr[ refIndex ] );
		}

		nodeType = builderNodeArrayPtr[ builderIndex ]->getNodeType( );
		// 定点节点
		if( nodeType == NodeEnum::NodeType::Point ) {
			if( erroRefOutputNode.size( ) == 0 )
				continue;
			erroNode.emplace_back( std::pair( builderNodeArrayPtr[ builderIndex ], std::pair( erroRefInputNode, erroRefOutputNode ) ) );
			continue;
		}
		refCount = builderNodeArrayPtr[ builderIndex ]->otherNodeOutputPortRefThisNodeInputPortVector.size( );
		if( refCount != 0 ) {
			refArrayPtr = builderNodeArrayPtr[ builderIndex ]->otherNodeOutputPortRefThisNodeInputPortVector.data( );
			for( refIndex = 0, findNodeIndex = 0; refIndex < refCount; ++refIndex, findNodeIndex = 0 )
				if( ArrayTools::findIndex( builderNodeArrayPtr, builderNodeArrayCount, refArrayPtr[ refIndex ], findNodeIndex ) == false )
					erroRefInputNode.emplace_back( refArrayPtr[ refIndex ] );
		}
		// 如果存在错误列表，则存储到错误信息
		if( erroRefInputNode.size( ) != 0 || erroRefOutputNode.size( ) != 0 )
			erroNode.emplace_back( std::pair( builderNodeArrayPtr[ builderIndex ], std::pair( erroRefInputNode, erroRefOutputNode ) ) );
		else if( refCount == 0 )
			// 输入依赖为 0，则放入开始列表
			beginNodeVector.emplace_back( builderNodeArrayPtr[ builderIndex ] );
	}
	findNodeIndex = erroReadNode.size( );
	refCount = erroNode.size( );
	if( refCount == 0 && findNodeIndex == 0 )
		// 没有错误信息，则返回 true
		return true;
	nodeDirector = appinstancePtr->getNodeDirector( );
	if( refCount ) {
		errorMapArray = erroNode.data( );
		errorNodeMsgFormat = tr( "[%1] 发现错误节点->%2" );
		errorRefInMsgFormat = tr( "\n\t缺少输入依赖 : \n\t%1" );
		errorRefOutMsgFormat = tr( "\n\t缺少输出依赖 : \n\t%1" );
		for( refIndex = 0; refIndex < refCount; ++refIndex ) {
			errorMapArray[ refIndex ].first->setNodeStyle( NodeEnum::NodeStyleType::Error );
			nodeTypeName = errorMapArray[ refIndex ].first->toQString( );
			appendErrorMsg = errorNodeMsgFormat.arg( refIndex ).arg( nodeTypeName );
			builderIndex = errorMapArray[ refIndex ].second.first.size( );
			if( builderIndex )
				appendErrorMsg = appendErrorMsg + errorRefInMsgFormat.arg( nodeDirector->nodeArrayToString( errorMapArray[ refIndex ].second.first ) );
			builderIndex = errorMapArray[ refIndex ].second.second.size( );
			if( builderIndex )
				appendErrorMsg = appendErrorMsg + errorRefInMsgFormat.arg( nodeDirector->nodeArrayToString( errorMapArray[ refIndex ].second.second ) );
			errorMsgList.append( appendErrorMsg );
		}
	}

	if( findNodeIndex )
		errorMsgList.append( tr( "准备状态出现问题:\n\t%1" ).arg( nodeDirector->nodeArrayToString( erroReadNode ) ) );
	appendErrorMsg = errorMsgList.join( "\n-----\n" );
	printerDirector = appinstancePtr->getPrinterDirector( );
	printerDirector->info( appendErrorMsg,Create_SrackInfo( ) );
	// 错误返回 false
	return false;
}
bool NodeRunInfo::isRunNode( Node *check_next_node ) {
	Node **overNodeArrayPtr;
	size_t overNodeIndex;
	size_t needRunNodeIndex;
	Node *needNode;
	NodeEnum::NodeType needNodeType;
	std::vector< Node * > resultNeedNodeVector;
	size_t needRunNodeArratCount;
	Node **needRunNodeArrayPtr;
	std::vector< Node * > resultAdviseNodeVector;
	size_t adviseCount;
	Node **nodeArrayPtr;

	if( check_next_node->fillInputPortCall( *builderDataTime, resultNeedNodeVector, currentFrame ) == false )
		return false; // 输入要求获取异常
	needRunNodeArratCount = resultNeedNodeVector.size( );
	if( needRunNodeArratCount == 0 )
		return true; // 不需要满足
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
		if( isOverRunNode( needNode ) == false )
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
	// 匹配开始节点

	for( findNodeArrayIndex = 0; findNodeArrayIndex < beginNodeArrayCount; findNodeArrayIndex += 1 )
		if( beginNodeArrayPtr[ findNodeArrayIndex ] == nullptr )
			continue;
		else if( isOverRunNode( beginNodeArrayPtr[ findNodeArrayIndex ] ) == true )
			continue;
		else if( isRunNode( beginNodeArrayPtr[ findNodeArrayIndex ] ) == true ) {
			result_run_node = beginNodeArrayPtr[ findNodeArrayIndex ];
			return true;
		}
	findNodeArrayCount = adviseNodeVector.size( );
	// 建议列表存在时，遍历建议列表，并且从中获取一个可运行节点
	if( findNodeArrayCount != 0 ) {
		findNodeArrayPtr = adviseNodeVector.data( );
		for( findNodeArrayIndex = 0; findNodeArrayIndex < findNodeArrayCount; findNodeArrayIndex += 1 )
			if( findNodeArrayPtr[ findNodeArrayIndex ] == nullptr )
				continue;
			else if( isRunNode( findNodeArrayPtr[ findNodeArrayIndex ] ) == true ) {
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
			if( isRunNode( findNodeArrayPtr[ findNodeArrayIndex ] ) == true == true ) {
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
bool NodeRunInfo::runNextValidNode( ) {
	Node *findResultRunNode = nullptr;
	do {
		if( findNextRunNode( findResultRunNode ) == false ) {
			// 清除已运行列表
			overRunNodeVector.clear( );
			overRunNodeArrayPtr = overRunNodeVector.data( );
			overRunNodeArrayCount = overRunNodeVector.size( );
			currentFrame = currentFrame + 1;
			if( maxFrame == currentFrame )
				currentFrame = 0;
			else
				currentFrame = currentFrame + 1;
			appinstancePtr->processEvents( );
			continue;
		}
		if( findResultRunNode == nullptr )
			continue;
		if( currentRunPtr != findResultRunNode )
			break;
	} while( findResultRunNode == nullptr );
	if( runCurrentNode( findResultRunNode ) == false )
		return false;
	appinstancePtr->processEvents( );
	if( overRunNode( ) == false )
		return false;
	appinstancePtr->processEvents( );
	if( filterToAdviseVector( ) == false )
		return false;
	appinstancePtr->processEvents( );
	overRunNodeVector.emplace_back( findResultRunNode );
	overRunNodeArrayPtr = overRunNodeVector.data( );
	overRunNodeArrayCount = overRunNodeVector.size( );
	return true;
}
bool NodeRunInfo::runNextNode( ) {
	if( isRunStop == false )
		return false;
	return runNextValidNode( );
}
bool NodeRunInfo::runResidueNode( ) {
	isRunStop = false;
	std::chrono::milliseconds milliseconds;
	long long count;
	do {
		if( runNextValidNode( ) == false )
			return false;
		appinstancePtr->processEvents( );
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
	builderNodeArrayPtr = nullptr;
	builderNodeArrayCount = 0;
	overRunNodeArrayPtr = nullptr;
	overRunNodeArrayCount = 0;
	beginNodeArrayPtr = nullptr;
	beginNodeArrayCount = 0;
	emit clear_signal( this, Create_SrackInfo( ) );
}
