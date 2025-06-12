#include "intTypeObject.h"
size_t IntTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	std_vector< uint8_t > resultData;
	if( serializeToVectorData( &resultData ) == false )
		return 0;
	auto resultDataCount = resultData.size( );
	if( resultDataCount > data_count /* 如果数据源小于当前序列化数据，则返回 */ )
		return 0;
	auto resultDataPtr = resultData.data( );
	if( *resultDataPtr == *read_data_vector /* 比较大小端 */ ) /* 大小端相同 */ {
		type_size_t resultDataLen = *( ( type_size_t * ) ( resultDataPtr + 1 ) );
		type_size_t readDataLen = *( ( type_size_t * ) ( read_data_vector + 1 ) );
		if( resultDataLen != readDataLen /* 长度是否匹配 */ )
			return 0;
		// 获取值的长度
		type_size_t valSize = sizeof( val );
		type_size_t start = sizeof( uint8_t ) + sizeof( type_size_t );
		// 比较个数 = 总长度 - 值长度 - 大小端标识长度 - 数据本身长度
		type_size_t equLen = resultDataCount - start - valSize;
		// 比较的下表
		type_size_t index = 0;
		for( ; index < equLen; ++index )
			if( resultDataPtr[ index + start ] != read_data_vector[ index + start ] )
				return 0;
		auto ptrIndex = index + start;
		auto converPtr = ( decltype(val) * ) ( read_data_vector + ptrIndex );
		val = *converPtr;
		return readDataLen;
	} else {
		type_size_t resultDataLen = *( ( type_size_t * ) ( resultDataPtr + 1 ) );
		type_size_t readDataLen = *( ( type_size_t * ) ( read_data_vector + 1 ) );
		// 反转长度
		converEndian( readDataLen, sizeof( readDataLen ) );
		if( resultDataLen != readDataLen /* 长度是否匹配 */ )
			return 0;
		// 获取值的长度
		type_size_t valSize = sizeof( val );
		type_size_t start = sizeof( uint8_t ) + sizeof( type_size_t );
		// 比较个数 = 总长度 - 值长度 - 大小端标识长度 - 数据本身长度
		type_size_t equLen = resultDataCount - start - valSize;
		// 比较的下表
		type_size_t index = 0;
		for( ; index < equLen; ++index )
			if( resultDataPtr[ index + start ] != read_data_vector[ index + start ] )
				return 0;
		auto ptrIndex = index + start;
		auto converPtr = ( decltype(val) * ) ( read_data_vector + ptrIndex );
		// 反转值
		converEndian( *converPtr, sizeof( readDataLen ) );
		val = *converPtr;
		return readDataLen;
	}
	return 0;
}
bool IntTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	auto object = metaObject( );
	QStringList classNameList;
	classNameList.append( object->className( ) );
	do {
		object = object->superClass( );
		if( object == nullptr )
			break;
		classNameList.append( object->className( ) );
	} while( true );
	QString classList = "{" + classNameList.join( "," ) + "}";
	QByteArray utf8 = classList.toUtf8( );
	qint64 utfCount = utf8.size( );
	type_size_t utfCharSize = utfCount * sizeof( utf8[ 0 ] );
	auto type_name_date = utf8.data( );
	// 所有数据的长度 = 类型+统计类型+对象值+大小端
	type_size_t dataCount = sizeof( uint8_t ) + sizeof( type_size_t ) + utfCharSize + sizeof( val );
	// 存储访问保存数据下标
	type_size_t index = 0;
	result_data_vector->resize( dataCount );

	// 配置大小端
	auto beg = isBegEndian( );
	auto dataPtr = result_data_vector->data( );
	dataPtr[ index ] = beg;
	// 存储转换列表
	std_vector< uint8_t > toDataVector;
	// 存储转换列表的起始指针
	uint8_t *sourceDataPtr;
	// 存储转换列表的个数
	type_size_t sourceCount;
	toData( dataCount, &toDataVector );
	// 偏移下标
	size_t orgIndex = index + 1;
	sourceCount = toDataVector.size( );
	sourceDataPtr = toDataVector.data( );
	for( index = 0; index < sourceCount; ++index )
		dataPtr[ index + orgIndex ] = sourceDataPtr[ index ];
	orgIndex = index + orgIndex;
	for( index = 0; index < utfCharSize; ++index )
		dataPtr[ index + orgIndex ] = type_name_date[ index ];

	toData( val, &toDataVector );
	orgIndex = index + orgIndex;
	sourceCount = toDataVector.size( );
	sourceDataPtr = toDataVector.data( );
	for( index = 0; index < sourceCount; ++index )
		dataPtr[ index + orgIndex ] = sourceDataPtr[ index ];
	return dataCount;
}
