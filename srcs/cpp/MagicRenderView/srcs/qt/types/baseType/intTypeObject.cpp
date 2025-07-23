#include "intTypeObject.h"

#include "qt/stacks/varStack/IVarStack.h"
size_t IntTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	std_vector< uint8_t > resultData;

	auto object = metaObject( );
	// 获取值的长度
	type_size_t valSize = sizeof( val );
	auto nativeTypeName = typeNames( );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( &resultData, object, getStackTypeNames( ), nativeTypeName, valSize );

	auto resultDataCount = resultData.size( );
	if( resultDataCount > data_count /* 如果数据源小于当前序列化数据，则返回 */ ) {
		tools::debug::printError( "无法满足对象信息序列化校验需求" );
		return false;
	}
	auto resultDataPtr = resultData.data( );
	bool cond = *resultDataPtr != *read_data_vector;
	type_size_t resultDataLen = *( ( type_size_t * ) ( resultDataPtr + 1 ) );
	type_size_t readDataLen = *( ( type_size_t * ) ( read_data_vector + 1 ) );
	// 反转长度
	if( cond )
		converEndian( readDataLen, sizeof( readDataLen ) );
	if( resultDataLen != readDataLen /* 长度是否匹配 */ ) {
		tools::debug::printError( "所需数据大于提供的参数" );
		return false;
	}
	type_size_t start = sizeof( uint8_t ) + sizeof( type_size_t );
	for( ; ( resultDataPtr + start ) != lastDataPtr; ++start )
		if( resultDataPtr[ start ] != read_data_vector[ start ] ) {
			tools::debug::printError( "类型信息不匹配" );
			return false;
		}
	// 反转值
	val = *( ( decltype(val) * ) ( read_data_vector + start ) );
	if( cond )
		converEndian( val, sizeof( readDataLen ) );
	return readDataLen;
}
bool IntTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	auto object = metaObject( );
	auto nativeTypeName = typeNames( );
	auto stackTypeName = getStackTypeNames( );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( result_data_vector, object, stackTypeName, nativeTypeName, sizeof( val ) );
	*( decltype(val) * ) lastDataPtr = val;
	return result_data_vector->size( );
}
