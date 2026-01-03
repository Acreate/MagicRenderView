#include "nodeTools.h"

#include "../../tools/arrayTools.h"
#include "../../tools/vectorTools.h"
#include "../node/node.h"
bool NodeTools::getNodeInputNodeRef( Node *check_node, std::vector< Node * > &result_ref_node_vector ) {
	if( check_node == nullptr )
		return false;
	std::vector< Node * > buffInputRef;
	std::vector< Node * > buffOutputRef;
	size_t count;
	size_t index;
	Node **nodeArrayPtr;

	result_ref_node_vector.append_range( check_node->refInputPortNode );
	count = check_node->refInputPortNode.size( );
	nodeArrayPtr = check_node->refInputPortNode.data( );
	for( index = 0; index < count; index += 1 ) {
		if( getNodeOutputNodeRef( nodeArrayPtr[ index ], buffOutputRef ) == false )
			return false;
		result_ref_node_vector.append_range( buffOutputRef );
		buffOutputRef.clear( );
	}
	for( index = 0; index < count; index += 1 ) {
		if( getNodeInputNodeRef( nodeArrayPtr[ index ], buffInputRef ) == false )
			return false;
		result_ref_node_vector.append_range( buffInputRef );
		buffInputRef.clear( );
	}
	return true;
}
bool NodeTools::getNodeOutputNodeRef( Node *check_node, std::vector< Node * > &result_ref_node_vector ) {
	if( check_node == nullptr )
		return false;
	std::vector< Node * > buffInputRef;
	std::vector< Node * > buffOutputRef;
	size_t count;
	size_t index;
	Node **nodeArrayPtr;

	result_ref_node_vector.append_range( check_node->refOutputPortNode );
	count = check_node->refOutputPortNode.size( );
	nodeArrayPtr = check_node->refOutputPortNode.data( );
	for( index = 0; index < count; index += 1 ) {
		if( getNodeInputNodeRef( nodeArrayPtr[ index ], buffInputRef ) == false )
			return false;
		result_ref_node_vector.append_range( buffInputRef );
		buffInputRef.clear( );
	}
	for( index = 0; index < count; index += 1 ) {
		if( getNodeOutputNodeRef( nodeArrayPtr[ index ], buffOutputRef ) == false )
			return false;
		result_ref_node_vector.append_range( buffOutputRef );
		buffOutputRef.clear( );
	}
	return true;
}
bool NodeTools::getNodeVectorRefNodeVector( const std::vector< Node * > &check_node_vector, std::vector< Node * > &result_ref_node_vector ) {
	// 覆盖，无法使用
	if( &check_node_vector == &result_ref_node_vector )
		return false;
	size_t checkCount = check_node_vector.size( );
	if( checkCount == 0 )
		return false;
	result_ref_node_vector.clear( );
	auto checkArrayPtr = check_node_vector.data( );
	size_t checkArrayIndex = 0;
	std::vector< Node * > inputRefNdoeVector;
	std::vector< Node * > outputRefNdoeVector;
	std::vector< Node * > buffRefNdoeVector;
	for( ; checkArrayIndex < checkCount; checkArrayIndex += 1 ) {
		if( getNodeInputNodeRef( checkArrayPtr[ checkArrayIndex ], inputRefNdoeVector ) == false )
			return false;
		buffRefNdoeVector.append_range( inputRefNdoeVector );
		if( getNodeOutputNodeRef( checkArrayPtr[ checkArrayIndex ], outputRefNdoeVector ) == false )
			return false;
		buffRefNdoeVector.append_range( outputRefNdoeVector );
		VectorTools::removeRepeat( buffRefNdoeVector, result_ref_node_vector );
		buffRefNdoeVector = result_ref_node_vector;
	}

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
