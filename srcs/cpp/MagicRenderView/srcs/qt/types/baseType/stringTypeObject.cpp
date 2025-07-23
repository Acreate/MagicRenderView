#include "stringTypeObject.h"

#include "qt/stacks/varStack/IVarStack.h"

size_t StringTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	std_vector< uint8_t > resultData;

	auto object = metaObject( );
	// 获取值的长度
	type_size_t valSize = sizeof( type_size_t );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( &resultData, object, getStackTypeNames( ), typeNames( ), valSize );

	auto resultDataCount = resultData.size( );
	if( resultDataCount > data_count /* 如果数据源小于当前序列化数据，则返回 */ ) {
		tools::debug::printError( "无法序列化该对象信息" );
		return false;
	}
	auto resultDataPtr = resultData.data( );
	/* 比较大小端 */
	bool cond = *resultDataPtr != *read_data_vector;

	type_size_t start = sizeof( uint8_t ) + sizeof( type_size_t );
	for( ; ( resultDataPtr + start ) != lastDataPtr; ++start )
		if( resultDataPtr[ start ] != read_data_vector[ start ] ) {
			tools::debug::printError( "类型信息不匹配" );
			return false;
		}
	// 数据应该反序列的长度
	type_size_t readDataLen = *( ( type_size_t * ) ( read_data_vector + 1 ) );
	if( cond )
		converEndian( readDataLen, sizeof( readDataLen ) );

	const uint8_t *text = read_data_vector + start;
	type_size_t strLen = *( ( decltype(strLen) * ) text );

	if( cond )
		converEndian( strLen, sizeof( strLen ) );

	// 反序列化长度 != ( 对象信息长度 + 序列化中的数据 )
	if( readDataLen != ( resultDataCount + strLen ) ) {
		tools::debug::printError( "所需数据大于提供的参数" );
		return false;
	}

	text = text + sizeof( type_size_t );
	QByteArray utf8;
	for( type_size_t index = 0; index < strLen; ++index )
		utf8.append( text[ index ] );
	string = QString( utf8 );

	return readDataLen;
}
bool StringTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	QByteArray utf8 = string.toUtf8( );
	qint64 qsizetype = utf8.size( );
	type_size_t strLen = qsizetype * sizeof( utf8[ 0 ] );
	auto object = metaObject( );
	size_t sizeType = sizeof( strLen );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( result_data_vector, object, getStackTypeNames( ), typeNames( ), sizeType + strLen );
	*( decltype(strLen) * ) lastDataPtr = strLen;
	lastDataPtr = lastDataPtr + sizeType;
	char *utfDataPtr = utf8.data( );
	for( type_size_t index = 0; index < strLen; ++index )
		lastDataPtr[ index ] = utfDataPtr[ index ];
	return result_data_vector->size( );
}
