#include "floatTypeObject.h"

#include "qt/stack/varStack/IVarStack.h"

size_t FloatTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	std_vector< uint8_t > resultData;

	auto object = metaObject( );
	// 获取值的长度
	type_size_t valSize = sizeof( val );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( &resultData, object,getStackTypeNames( ), typeNames( ), valSize );

	auto resultDataCount = resultData.size( );
	if( resultDataCount > data_count /* 如果数据源小于当前序列化数据，则返回 */ )
		return 0;
	auto resultDataPtr = resultData.data( );
	if( *resultDataPtr == *read_data_vector /* 比较大小端 */ ) /* 大小端相同 */ {
		type_size_t resultDataLen = *( ( type_size_t * ) ( resultDataPtr + 1 ) );
		type_size_t readDataLen = *( ( type_size_t * ) ( read_data_vector + 1 ) );
		if( resultDataLen != readDataLen /* 长度是否匹配 */ )
			return 0;
		type_size_t start = sizeof( uint8_t ) + sizeof( type_size_t );
		for( ; ( resultDataPtr + start ) != lastDataPtr; ++start )
			if( resultDataPtr[ start ] != read_data_vector[ start ] )
				return 0;
		val = *( ( decltype(val) * ) ( read_data_vector + start ) );
		return readDataLen;
	} else {
		type_size_t resultDataLen = *( ( type_size_t * ) ( resultDataPtr + 1 ) );
		type_size_t readDataLen = *( ( type_size_t * ) ( read_data_vector + 1 ) );
		// 反转长度
		converEndian( readDataLen, sizeof( readDataLen ) );
		if( resultDataLen != readDataLen /* 长度是否匹配 */ )
			return 0;
		type_size_t start = sizeof( uint8_t ) + sizeof( type_size_t );
		for( ; ( resultDataPtr + start ) != lastDataPtr; ++start )
			if( resultDataPtr[ start ] != read_data_vector[ start ] )
				return 0;
		// 反转值
		val = *( ( decltype(val) * ) ( read_data_vector + start ) );
		converEndian( val, sizeof( readDataLen ) );
		return readDataLen;
	}
	return 0;
}
bool FloatTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	auto object = metaObject( );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( result_data_vector, object, getStackTypeNames( ), typeNames( ), sizeof( val ) );
	*( decltype(val) * ) lastDataPtr = val;
	return result_data_vector->size( );
}
