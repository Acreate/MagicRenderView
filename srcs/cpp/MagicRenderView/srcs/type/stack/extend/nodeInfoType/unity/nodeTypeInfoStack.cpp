#include "nodeTypeInfoStack.h"

#include <define/macro.h>
#include <director/varDirector.h>
#include <node/nodeType/nodeTypeInfo.h>
#include <node/portType/portTypeInfo.h>

NodeTypeInfoStack::~NodeTypeInfoStack( ) {

}
bool NodeTypeInfoStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( , NodeTypeInfo, "NodeTypeInfo" );
	return true;
}
NodeTypeInfoStack::NodeTypeInfoStack( ) {
}

using t_current_unity_type = NodeTypeInfo;
bool NodeTypeInfoStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	// 匹配指向有效对象
	t_current_unity_type *converTarget = nullptr;
	if( hasVarPtr( result_obj_ptr ) == false ) {
		if( varDirector->create( converTarget ) == false || converTarget == nullptr )
			return false;
		result_obj_ptr = converTarget;
	} else
		converTarget = ( t_current_unity_type * ) result_obj_ptr;

	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	QString *stringPtr = nullptr;
	uint64_t *uint64Ptr = nullptr;
	int32_t *int32Ptr = nullptr;
	std::vector< uint8_t > *uint8DataVectorPtr = nullptr;
	void *converPtr;
	if( varDirector.create( stringPtr ) == false || stringPtr == nullptr )
		return false;
	if( varDirector.create( uint64Ptr ) == false || uint64Ptr == nullptr )
		return false;
	if( varDirector.create( int32Ptr ) == false || int32Ptr == nullptr )
		return false;
	if( varDirector.create( uint8DataVectorPtr ) == false || uint8DataVectorPtr == nullptr )
		return false;

	size_t modCount = obj_memory_size;
	const uint8_t *offsetPtr = obj_start_ptr;
	// 数据量是否满足填充数据
	converPtr = uint64Ptr;
	if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
		return false;
	modCount -= result_count;
	if( modCount < *uint64Ptr )
		return false;
	offsetPtr += result_count;

	// 获取节点名称
	converPtr = stringPtr;
	if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
		return false;
	if( stringPtr->isEmpty( ) )
		return false;
	converTarget->nodeName = *stringPtr;
	modCount -= result_count;
	offsetPtr += result_count;

	// 获取节点生成码
	converPtr = uint64Ptr;
	if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
		return false;
	modCount -= result_count;
	offsetPtr += result_count;
	converTarget->nodeGeneratorCode = *uint64Ptr;

	// 获取 x 坐标
	converPtr = int32Ptr;
	if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
		return false;
	modCount -= result_count;
	offsetPtr += result_count;
	converTarget->posX = *int32Ptr;

	// 获取 y 坐标
	if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
		return false;
	modCount -= result_count;
	offsetPtr += result_count;
	converTarget->posY = *int32Ptr;

	// 节点附加数据
	converPtr = uint8DataVectorPtr;
	if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
		return false;
	modCount -= result_count;
	offsetPtr += result_count;
	converTarget->nodeData = *uint8DataVectorPtr;

	// 获取链接信息
	converPtr = uint64Ptr;
	if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
		return false;
	offsetPtr += result_count;
	size_t portLinkIndex = 0;
	size_t portLinkCount = converTarget->portLinkInfoVector.size( );
	auto portTypeInfoArrayPtr = converTarget->portLinkInfoVector.data( );
	for( ; portLinkIndex < portLinkCount; ++portLinkIndex )
		delete portTypeInfoArrayPtr[ portLinkIndex ];
	converTarget->portLinkInfoVector.resize( *uint64Ptr, nullptr );
	if( *uint64Ptr != 0 ) {
		modCount -= result_count;
		portLinkCount = *uint64Ptr;
		portTypeInfoArrayPtr = converTarget->portLinkInfoVector.data( );
		portLinkIndex = 0;
		converPtr = uint64Ptr;
		for( ; portLinkIndex < portLinkCount; ++portLinkIndex ) {
			PortTypeInfo *portTypeInfo = new PortTypeInfo;
			portTypeInfoArrayPtr[ portLinkIndex ] = portTypeInfo;
			// 配置输出节点生成码
			if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
				return false;
			offsetPtr += result_count;
			modCount -= result_count;
			portTypeInfo->outputNodeGeneratorCode = *uint64Ptr;
			// 配置输出端口生成码
			if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
				return false;
			offsetPtr += result_count;
			modCount -= result_count;
			portTypeInfo->outputPortGeneratorCode = *uint64Ptr;
			// 配置输入节点生成码
			if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
				return false;
			offsetPtr += result_count;
			modCount -= result_count;
			portTypeInfo->inputNodeGeneratorCode = *uint64Ptr;
			// 配置输入节点生成码
			if( varDirector.toVar( result_count, offsetPtr, modCount, converPtr ) == false )
				return false;
			offsetPtr += result_count;
			modCount -= result_count;
			portTypeInfo->inputPortGeneratorCode = *uint64Ptr;
		}
	}
	result_count = offsetPtr - obj_start_ptr;
	return true;
}
TypeEnum::Type NodeTypeInfoStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool NodeTypeInfoStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	t_current_unity_type *converTarget = ( NodeTypeInfo * ) obj_start_ptr;
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	QString *stringPtr = nullptr;
	uint64_t *uint64Ptr = nullptr;
	int32_t *int32Ptr = nullptr;
	std::vector< uint8_t > *uint8DataVectorPtr = nullptr;;
	if( varDirector.create( stringPtr ) == false || stringPtr == nullptr )
		return false;
	if( varDirector.create( uint64Ptr ) == false || uint64Ptr == nullptr )
		return false;
	if( varDirector.create( int32Ptr ) == false || int32Ptr == nullptr )
		return false;
	if( varDirector.create( uint8DataVectorPtr ) == false || uint8DataVectorPtr == nullptr )
		return false;
	std::vector< uint8_t > buff;
	result_data.clear( );
	// 节点名称
	*stringPtr = converTarget->nodeName;
	if( varDirector.toVector( stringPtr, buff ) == false )
		return false;
	result_data.append_range( buff );

	// 节点生成码
	*uint64Ptr = converTarget->nodeGeneratorCode;
	if( varDirector.toVector( uint64Ptr, buff ) == false )
		return false;
	result_data.append_range( buff );

	// 节点 x 坐标
	*int32Ptr = converTarget->posX;
	if( varDirector.toVector( int32Ptr, buff ) == false )
		return false;
	result_data.append_range( buff );

	// 节点 y 坐标
	*int32Ptr = converTarget->posY;
	if( varDirector.toVector( int32Ptr, buff ) == false )
		return false;
	result_data.append_range( buff );

	// 节点附加数据
	*uint8DataVectorPtr = converTarget->nodeData;
	if( varDirector.toVector( uint8DataVectorPtr, buff ) == false )
		return false;
	result_data.append_range( buff );

	// 链接信息
	*uint64Ptr = converTarget->portLinkInfoVector.size( );
	if( varDirector.toVector( uint64Ptr, buff ) == false )
		return false;
	result_data.append_range( buff );
	if( *uint64Ptr != 0 ) {
		auto portTypeInfoArrayPtr = converTarget->portLinkInfoVector.data( );
		size_t index = 0;
		size_t count = *uint64Ptr;
		for( ; index < count; ++index ) {
			// 输出节点生成码
			*uint64Ptr = portTypeInfoArrayPtr[ index ]->outputNodeGeneratorCode;
			if( varDirector.toVector( uint64Ptr, buff ) == false )
				return false;
			result_data.append_range( buff );
			// 输出端口生成码
			*uint64Ptr = portTypeInfoArrayPtr[ index ]->outputPortGeneratorCode;
			if( varDirector.toVector( uint64Ptr, buff ) == false )
				return false;
			result_data.append_range( buff );
			// 输入节点生成码
			*uint64Ptr = portTypeInfoArrayPtr[ index ]->inputNodeGeneratorCode;
			if( varDirector.toVector( uint64Ptr, buff ) == false )
				return false;
			result_data.append_range( buff );
			// 输入端口生成码
			*uint64Ptr = portTypeInfoArrayPtr[ index ]->inputPortGeneratorCode;
			if( varDirector.toVector( uint64Ptr, buff ) == false )
				return false;
			result_data.append_range( buff );
		}
	}

	// 总数据长度
	*uint64Ptr = result_data.size( );
	if( varDirector.toVector( uint64Ptr, buff ) == false )
		return false;
	buff.append_range( result_data );
	result_data = buff;
	return true;
}
