#include "stringTypeObject.h"

size_t StringTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
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
		type_size_t resultDataLen = *( ( type_size_t * ) ( resultDataPtr + 1 ) );
		type_size_t readDataLen = *( ( type_size_t * ) ( read_data_vector + 1 ) );
		if( resultDataLen != readDataLen /* 长度是否匹配 */ )
			return 0;
		type_size_t start = sizeof( uint8_t ) + sizeof( type_size_t );
		for( ; ( resultDataPtr + start ) != lastDataPtr; ++start )
			if( resultDataPtr[ start ] != read_data_vector[ start ] )
				return 0;
		const uint8_t *text = read_data_vector + start;
		type_size_t strLen = *( ( decltype(strLen) * ) text );
		text = text + sizeof( type_size_t );
		QByteArray utf8;

		for( type_size_t index = 0; index < strLen; ++index )
			utf8.append( text[ index ] );
		string = QString( utf8 );
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
		QByteArray utf8;

		for( type_size_t index = 0; index < strLen; ++index )
			utf8.append( text[ index ] );
		string = QString( utf8 );
		return readDataLen;
	}
	return 0;
}
bool StringTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	QByteArray utf8 = string.toUtf8( );
	type_size_t strLen = utf8.size( ) * sizeof( utf8[ 0 ] );
	auto object = metaObject( );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( result_data_vector, object, typeNames( ), sizeof( strLen ) );
	*( decltype(strLen) * ) lastDataPtr = strLen;
	size_t size = result_data_vector->size( );
	result_data_vector->resize( size + strLen );
	auto data = result_data_vector->data( ) + size;
	auto utfDataPtr = utf8.data( );
	for( type_size_t index = 0; index < strLen; ++index )
		data[ index ] = utfDataPtr[ index ];
	return result_data_vector->size( );
}
