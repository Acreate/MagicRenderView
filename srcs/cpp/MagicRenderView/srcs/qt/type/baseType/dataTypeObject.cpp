#include "dataTypeObject.h"

#include "qt/stack/varStack/IVarStack.h"

size_t DataTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	std_vector< uint8_t > resultData;

	auto object = metaObject( );
	// 获取值的长度
	type_size_t valSize = sizeof( type_size_t );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( &resultData, object, getStackTypeNames( ), typeNames( ), valSize );

	auto resultDataCount = resultData.size( );
	if( resultDataCount > data_count /* 如果数据源小于当前序列化数据，则返回 */ )
		return 0;
	auto resultDataPtr = resultData.data( );
	type_size_t start = sizeof( uint8_t ) + sizeof( type_size_t );
	for( ; ( resultDataPtr + start ) != lastDataPtr; ++start )
		if( resultDataPtr[ start ] != read_data_vector[ start ] )
			return 0;
	// 比较大小端
	bool cond = *resultDataPtr != *read_data_vector;
	const uint8_t *text = read_data_vector + start;
	start = *( ( decltype(start) * ) text );
	if( cond ) // 大小端逆转
		converEndian( start, sizeof( start ) );
	text = text + sizeof( type_size_t );
	val->clear( );
	for( type_size_t index = 0; index < start; ++index )
		val->emplace_back( text[ index ] );
	return start;
}
bool DataTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	type_size_t strLen = val->size( );
	auto object = metaObject( );
	size_t typeSize = sizeof( strLen );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( result_data_vector, object, getStackTypeNames( ), typeNames( ), typeSize + strLen );
	*( decltype(strLen) * ) lastDataPtr = strLen;
	lastDataPtr = lastDataPtr + typeSize;
	auto utfDataPtr = val->data( );
	for( type_size_t index = 0; index < strLen; ++index )
		lastDataPtr[ index ] = utfDataPtr[ index ];
	return result_data_vector->size( );
}
