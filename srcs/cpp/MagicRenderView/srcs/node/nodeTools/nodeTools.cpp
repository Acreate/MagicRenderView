#include "nodeTools.h"

#include "../../tools/arrayTools.h"
#include "../../tools/vectorTools.h"
#include "../node/node.h"
bool NodeTools::getNodeVectorRefNodeVector( const std::vector< Node * > &check_node_vector, std::vector< Node * > &result_ref_node_vector ) {
	// 覆盖，无法使用
	if( &check_node_vector == &result_ref_node_vector )
		return false;
	size_t checkCount = check_node_vector.size( );
	if( checkCount == 0 )
		return false;
	auto checkArrayPtr = check_node_vector.data( );
	size_t checkArrayIndex = 0;

	// 临时存储输入依赖
	std::vector< Node * > buffInputRefNdoeVector;
	size_t buffInputRefCount;
	Node **buffInputRefArray;
	size_t buffInputIndex;
	// 临时存储输出依赖
	std::vector< Node * > buffOutputRefNdoeVector;
	size_t buffOutputRefCount;
	Node **buffOutputRefArray;
	size_t buffOutputIndex;
	// 临时存储依赖
	std::vector< Node * > buffRefNdoeVector = check_node_vector;
	auto buffRefArray = buffRefNdoeVector.data( );
	size_t buffRefCount = buffRefNdoeVector.size( );
	size_t buffRefIndex;
	// 下次循环节点
	std::vector< Node * > nextNode;
	std::vector< Node * > buffNextNode;
	// 过滤节点
	std::vector< Node * > filterNode;
	size_t filterNodeRefCount = filterNode.size( );
	Node **filterNodeRefArray = filterNode.data( );
	size_t filterNodeIndex;
	do {
		for( ; checkArrayIndex < checkCount; checkArrayIndex += 1 ) {

			// 获取节点的输入依赖
			buffInputRefNdoeVector = checkArrayPtr[ checkArrayIndex ]->refInputPortNode;
			buffInputRefCount = buffInputRefNdoeVector.size( );
			if( buffInputRefCount ) {
				buffInputRefArray = buffInputRefNdoeVector.data( );
				for( buffInputIndex = 0; buffInputIndex < buffInputRefCount; buffInputIndex += 1 ) {
					for( buffRefIndex = 0; buffRefIndex < buffRefCount; buffRefIndex += 1 )
						if( buffRefArray[ buffRefIndex ] == buffInputRefArray[ buffInputIndex ] )
							break;
					if( buffRefIndex == buffRefCount )
						continue;
					buffInputRefArray[ buffInputIndex ] = nullptr;
				}
				ArrayTools::sortNullptr( buffInputRefArray, buffInputRefCount );
				for( buffInputIndex = 0; buffInputIndex < buffInputRefCount; buffInputIndex += 1 )
					if( buffInputRefArray[ buffInputIndex ] == nullptr )
						break;
				if( buffInputIndex ) {
					buffInputRefCount = buffRefCount + buffInputIndex;//增加长度
					buffRefNdoeVector.resize( buffInputRefCount ); // 重构大小
					buffRefArray = buffRefNdoeVector.data( ); // 指向新的地址
					for( buffInputIndex = 0; buffRefCount < buffInputRefCount; buffRefCount += 1, buffInputIndex += 1 ) {
						buffRefArray[ buffRefCount ] = buffInputRefArray[ buffInputIndex ]; // 新的大小
						for( filterNodeIndex = 0; filterNodeIndex < filterNodeRefCount; filterNodeIndex += 1 )
							if( filterNodeRefArray[ filterNodeIndex ] == buffInputRefArray[ buffInputIndex ] )
								break;
						if( filterNodeIndex < filterNodeRefCount )
							continue; // 过滤
						nextNode.emplace_back( buffInputRefArray[ buffInputIndex ] ); // 加入到下次遍历
						filterNode.emplace_back( buffInputRefArray[ buffInputIndex ] ); // 加入到过滤
						filterNodeRefCount += 1;
						filterNodeRefArray = filterNode.data( );
					}
				}
			}

			// 获取节点的输出依赖
			buffOutputRefNdoeVector = checkArrayPtr[ checkArrayIndex ]->refOutputPortNode;
			buffOutputRefCount = buffOutputRefNdoeVector.size( );
			if( buffOutputRefCount ) {
				buffOutputRefArray = buffOutputRefNdoeVector.data( );
				for( buffOutputIndex = 0; buffOutputIndex < buffOutputRefCount; buffOutputIndex += 1 ) {
					for( buffRefIndex = 0; buffRefIndex < buffRefCount; buffRefIndex += 1 )
						if( buffRefArray[ buffRefIndex ] == buffOutputRefArray[ buffOutputIndex ] )
							break;
					if( buffRefIndex == buffRefCount )
						continue;
					buffOutputRefArray[ buffOutputIndex ] = nullptr;
				}
				ArrayTools::sortNullptr( buffOutputRefArray, buffOutputRefCount );
				for( buffOutputIndex = 0; buffOutputIndex < buffOutputRefCount; buffOutputIndex += 1 )
					if( buffOutputRefArray[ buffOutputIndex ] == nullptr )
						break;
				if( buffOutputIndex ) {
					buffOutputRefCount = buffRefCount + buffOutputIndex;//增加长度
					buffRefNdoeVector.resize( buffOutputRefCount ); // 重构大小
					buffRefArray = buffRefNdoeVector.data( ); // 指向新的地址
					for( buffOutputIndex = 0; buffRefCount < buffOutputRefCount; buffRefCount += 1, buffOutputIndex += 1 ) {
						buffRefArray[ buffRefCount ] = buffOutputRefArray[ buffOutputIndex ]; // 新的大小
						for( filterNodeIndex = 0; filterNodeIndex < filterNodeRefCount; filterNodeIndex += 1 )
							if( filterNodeRefArray[ filterNodeIndex ] == buffOutputRefArray[ buffOutputIndex ] )
								break;
						if( filterNodeIndex < filterNodeRefCount )
							continue; // 过滤
						nextNode.emplace_back( buffOutputRefArray[ buffOutputIndex ] ); // 加入到下次遍历
						filterNode.emplace_back( buffOutputRefArray[ buffOutputIndex ] ); // 加入到过滤
						filterNodeRefCount += 1;
						filterNodeRefArray = filterNode.data( );
					}
				}
			}
		}
		checkCount = nextNode.size( );
		// 遍历完毕
		if( checkCount == 0 )
			break;
		buffNextNode = nextNode;
		// 存在则重新遍历
		checkArrayPtr = buffNextNode.data( );
		nextNode.clear( );
	} while( true );

	if( sortNodeVectorRefNodeVector( buffRefNdoeVector, result_ref_node_vector ) == false )
		return false;
	return true;

}
bool NodeTools::sortNodeVectorRefNodeVector( const std::vector< Node * > &check_node_vector, std::vector< Node * > &result_ref_node_vector ) {
	// 覆盖，无法使用
	if( &check_node_vector == &result_ref_node_vector )
		return false;
	size_t checkCount = check_node_vector.size( );
	if( checkCount == 0 )
		return false;
	std::vector< Node * > sortBuff;
	// 去重
	VectorTools::removeRepeat( check_node_vector, sortBuff );
	checkCount = sortBuff.size( );
	result_ref_node_vector = std::vector< Node * >( checkCount, nullptr );
	auto destArrayPtr = result_ref_node_vector.data( );
	auto sourArrayPtr = sortBuff.data( );
	size_t sourIndex;
	size_t sourLen;
	size_t destIndex = 0;
	size_t destLen = 0;
	size_t findIndex;
	Node **refInputPortNodeArrayPtr;
	size_t refInputPortNodeArrayIndex;
	do {
		for( sourIndex = 0; sourIndex < checkCount; sourIndex += 1 ) {
			size_t refInputPortNodeArrayCount = sourArrayPtr[ sourIndex ]->refInputPortNode.size( );
			if( refInputPortNodeArrayCount != 0 ) {
				refInputPortNodeArrayPtr = sourArrayPtr[ sourIndex ]->refInputPortNode.data( );
				refInputPortNodeArrayIndex = 0;
				findIndex = 0;
				for( ; refInputPortNodeArrayIndex < refInputPortNodeArrayCount; refInputPortNodeArrayIndex += 1, findIndex = 0 )
					if( ArrayTools::findIndex( destArrayPtr, destIndex, refInputPortNodeArrayPtr[ refInputPortNodeArrayIndex ], findIndex ) == false )
						break; // 列表不存在，则退出循环，说明依赖依然仍然未知（未排序）
				if( refInputPortNodeArrayIndex < refInputPortNodeArrayCount )
					continue;
			}
			findIndex = 0;
			if( ArrayTools::findIndex( destArrayPtr, destIndex, sourArrayPtr[ sourIndex ], findIndex ) == true )
				continue; // 列表当中已经存在，则遍历下一次
			destArrayPtr[ destIndex ] = sourArrayPtr[ sourIndex ];
			sourArrayPtr[ sourIndex ] = nullptr;
			destIndex += 1; // 下标自增 1
		}
		if( destLen == destIndex )
			return false;// 遍历一次后，不存在有效长度，则返回
		for( sourIndex = 0, sourLen = 0; sourIndex < checkCount; sourIndex += 1 )
			if( sourArrayPtr[ sourIndex ] != nullptr ) {
				sourLen += 1;
			}
		if( sourLen == 0 )
			break;//所有元素都为 nullptr
		// 所有 nullptr 排序到末尾
		ArrayTools::sortNullptr( sourArrayPtr, checkCount );
		// 真实长度
		checkCount = sourLen;
	} while( true );

	result_ref_node_vector.resize( destIndex ); // 根据下标进行大小缩放
	return true;
}
