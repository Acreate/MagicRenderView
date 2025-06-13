#include "dataTypeObject.h"

size_t DataTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	std_vector< uint8_t > resultData;

	auto object = metaObject( );
	// 获取值的长度
	type_size_t valSize = sizeof( type_size_t );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( &resultData, object, typeNames( ), valSize );

	auto resultDataCount = resultData.size( );
	if( resultDataCount > data_count /* 如果数据源小于当前序列化数据，则返回 */ )
		return 0;
	auto resultDataPtr = resultData.data( );
	if( *resultDataPtr == *read_data_vector /* 比较大小端 */ ) /* 大小端相同 */ {
		type_size_t readDataLen = *( ( type_size_t * ) ( read_data_vector + 1 ) );
		type_size_t start = sizeof( uint8_t ) + sizeof( type_size_t );
		for( ; ( resultDataPtr + start ) != lastDataPtr; ++start )
			if( resultDataPtr[ start ] != read_data_vector[ start ] )
				return 0;
		const uint8_t *text = read_data_vector + start;
		type_size_t strLen = *( ( decltype(strLen) * ) text );
		text = text + sizeof( type_size_t );
		val->clear( );
		for( type_size_t index = 0; index < strLen; ++index )
			val->emplace_back( text[ index ] );
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
		const uint8_t *text = read_data_vector + start;
		type_size_t strLen = *( ( decltype(strLen) * ) text );
		converEndian( strLen, sizeof( strLen ) );
		text = text + sizeof( type_size_t );
		val->clear( );
		for( type_size_t index = 0; index < strLen; ++index )
			val->emplace_back( text[ index ] );
		return readDataLen;
	}
	return 0;
}
bool DataTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	type_size_t strLen = val->size( );
	auto object = metaObject( );
	size_t typeSize = sizeof( strLen );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( result_data_vector, object, typeNames( ), typeSize + strLen );
	*( decltype(strLen) * ) lastDataPtr = strLen;
	lastDataPtr = lastDataPtr + typeSize;
	auto utfDataPtr = val->data( );
	for( type_size_t index = 0; index < strLen; ++index )
		lastDataPtr[ index ] = utfDataPtr[ index ];
	return result_data_vector->size( );
}
