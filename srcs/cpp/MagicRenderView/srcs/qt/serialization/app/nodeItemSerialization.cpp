#include "./nodeItemSerialization.h"
#include <qt/node/item/nodeItem.h>
#include <qt/node/prot/NodePort.h>

#include <qt/generate/nodeItemGenerate.h>

#include "../../node/prot/outputProt/nodeOutputPort.h"

NodeItemSerialization::NodeItemSerialization( ) {
	auto &typeInfo = typeid( t_current_type );
	typeName = typeInfo.name( );
}
size_t NodeItemSerialization::fillUnityBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	if( var_type == nullptr )
		return 0;

	ConverPtr( dataPtr, var_type, const NodeItem* );
	std_vector< uint8_t > buff;
	std_vector< uint8_t > resultBuff;
	// 节点类名
	serialization.fillBinVector( typeName, buff );
	resultBuff.append_range( buff );
	// 节点目录名称
	serialization.fillBinVector( dataPtr->getMetaObjectDir( ), buff );
	resultBuff.append_range( buff );
	// 节点名称
	serialization.fillBinVector( dataPtr->getMetaObjectName( ), buff );
	resultBuff.append_range( buff );
	// 节点编号
	serialization.fillBinVector( dataPtr->generateCode, buff );
	resultBuff.append_range( buff );
	// 节点 x 位置
	serialization.fillBinVector( dataPtr->nodePosX, buff );
	resultBuff.append_range( buff );
	// 节点 y 位置
	serialization.fillBinVector( dataPtr->nodePosY, buff );
	resultBuff.append_range( buff );
	// 节点链接个数
	serialization.fillBinVector( dataPtr->linkCode.size( ), buff );
	resultBuff.append_range( buff );
	// 节点链接端口
	size_t count = dataPtr->linkCode.size( ), index = 0;
	auto data = dataPtr->linkCode.data( );
	for( ; index < count; ++index ) {
		auto &pair = data[ index ];
		serialization.fillBinVector( pair.first->generateCode, buff );
		resultBuff.append_range( buff );
		serialization.fillBinVector( pair.second->generateCode, buff );
		resultBuff.append_range( buff );
		serialization.fillBinVector( pair.second->varCode, buff );
		resultBuff.append_range( buff );
	}

	serialization.fillBinVector( resultBuff.size( ), result_bin_data_vector );
	result_bin_data_vector.append_range( resultBuff );
	return result_bin_data_vector.size( );
}
size_t NodeItemSerialization::fillUnityObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	Fill_Obj_CheckMemoryType( NodeItem*, dataPtr, var_type, source_ptr, source_ptr_count, needCount, count, mod, offsetPtr, typeName, getTypeName, return 0 );

	QString nodeDirName, nodeName;
	// 节点目录名称
	count = serialization.fillObjVector( &nodeDirName, offsetPtr, mod );
	if( nodeDirName != dataPtr->getMetaObjectDir( ) )
		return 0;
	Next_Ptr( offsetPtr, mod, count );
	// 节点名称
	count = serialization.fillObjVector( &nodeName, offsetPtr, mod );
	if( nodeName != dataPtr->getMetaObjectName( ) )
		return 0;
	Next_Ptr( offsetPtr, mod, count );

	count = serialization.fillObjVector( &dataPtr->generateCode, offsetPtr, mod );
	Next_Ptr( offsetPtr, mod, count );

	count = serialization.fillObjVector( &dataPtr->nodePosX, offsetPtr, mod );
	Next_Ptr( offsetPtr, mod, count );

	count = serialization.fillObjVector( &dataPtr->nodePosY, offsetPtr, mod );
	Next_Ptr( offsetPtr, mod, count );

	count = serialization.fillObjVector( &needCount, offsetPtr, mod );
	Next_Ptr( offsetPtr, mod, count );
	dataPtr->linkCode.reserve( needCount );
	size_t index = 0;
	auto data = dataPtr->linkCode.data( );
	for( ; index < needCount; ++index ) {
		count = serialization.fillObjVector( &data[ index ].first->generateCode, offsetPtr, mod );
		Next_Ptr( offsetPtr, mod, count );
		count = serialization.fillObjVector( &data[ index ].second->generateCode, offsetPtr, mod );
		Next_Ptr( offsetPtr, mod, count );
		count = serialization.fillObjVector( &data[ index ].second->varCode, offsetPtr, mod );
		Next_Ptr( offsetPtr, mod, count );
	}
	return offsetPtr - source_ptr;
}
size_t NodeItemSerialization::fillVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return 0;
}
size_t NodeItemSerialization::fillVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return 0;
}
size_t NodeItemSerialization::fillPtrVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return serialization.fillPtrVectorBin< t_current_type >( this, var_type, result_bin_data_vector );
}
size_t NodeItemSerialization::fillPtrVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return serialization.fillPtrVectorObj< t_current_type >( this, var_type, source_ptr, source_ptr_count );
}
bool NodeItemSerialization::getNewObj( void **new_set_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {

	if( source_ptr == nullptr || source_ptr_count == 0 )
		return false;
	size_t needCount;
	auto count = serialization.fillObjVector( &needCount, source_ptr, source_ptr_count );
	size_t mod = source_ptr_count - count;
	if( needCount > mod )
		return false;
	auto offertPtr = source_ptr + count;
	QString getTypeName;
	count = serialization.fillObjVector( &getTypeName, offertPtr, mod );
	if( typeName != getTypeName )
		return false;
	offertPtr += count;
	mod -= count;

	QString nodeDirName, nodeName;
	// 节点目录名称
	count = serialization.fillObjVector( &nodeDirName, offertPtr, mod );
	Next_Ptr( offertPtr, mod, count );
	// 节点名称
	serialization.fillObjVector( &nodeName, offertPtr, mod );
	NodeItem *nodeItem = NodeItemGenerate::createNodeItem( nodeDirName, nodeName );
	if( nodeItem == nullptr )
		return false;
	*new_set_ptr = nodeItem;
	return true;
}
bool NodeItemSerialization::removeNewObj( void *new_set_ptr ) {
	delete ( t_current_type * ) new_set_ptr;
	return true;
}
