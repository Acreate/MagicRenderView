#include "./ISerialize.h"
#include <qt/type/ITypeObject.h>
#include <QList>

ISerialize::SerializeInfo::SerializeInfo( const uint8_t *data_ptr, const size_t &data_size ): data( data_size ) {
	isInitTrue = false;
	auto dataPtr = data.data( );
	for( size_t index = 0; index < data_size; ++index )
		dataPtr[ index ] = data_ptr[ index ];
}
bool ISerialize::SerializeInfo::init( ) {
	auto dataPtr = data.data( );
	size_t dataCount = data.size( );
	// 获取大小端
	begEndian = *dataPtr;
	uchar endian = getBegEndian( );
	size = *( type_size_t * ) ( dataPtr + 1 );
	if( begEndian != endian )
		converEndian( size );
	if( size < dataCount ) {
		tools::debug::printError( "数据是损坏的" );
		isInitTrue = false;
		return false;
	}
	// 找到类型
	dataPtr = dataPtr + 1 + sizeof( type_size_t );
	QByteArray hex;
	hex.resize( size );
	auto hexDataPtr = hex.data( );
	for( size_t index = 0; index < size; ++index )
		hexDataPtr[ index ] = dataPtr[ index ];
	// 找到 [] 
	QString structString( hex );
	qsizetype left = structString.indexOf( "[" );
	qsizetype right = structString.indexOf( "]", left );
	QString mid = structString.mid( left, right - left );
	auto stringList = mid.split( "," );
	typeNames.clear( );
	for( auto &unityString : stringList )
		typeNames.emplace_back( QByteArray::fromHex( unityString.toUtf8( ) ) );

	// 找到 {}
	left = structString.indexOf( "{", right );
	right = structString.indexOf( "}", left );
	mid = structString.mid( left, right - left );
	stringList = mid.split( "," );
	metaObjectClassNames.clear( );
	for( auto &unityString : stringList )
		metaObjectClassNames.emplace_back( QByteArray::fromHex( unityString.toUtf8( ) ) );
	// 配置数据起始地址
	infoLastPtr = dataPtr + size;
	return true;
}
uint8_t * ISerialize::converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QMetaObject *meta_object_ptr, const QStringList &native_type_name, const size_t &append_size ) {
	QStringList classNameList;

	for( auto &str : native_type_name )
		classNameList.append( str.toUtf8( ).toHex( ) );
	QString classList = "[" + classNameList.join( ", " );

	classNameList.clear( );
	QString className = meta_object_ptr->className( );
	classNameList.append( className.toUtf8( ).toHex( ) );
	do {
		meta_object_ptr = meta_object_ptr->superClass( );
		if( meta_object_ptr == nullptr )
			break;
		className = meta_object_ptr->className( );
		classNameList.append( className.toUtf8( ).toHex( ) );
	} while( true );

	classList = classList + "]:{" + classNameList.join( "," ) + "}";
	QByteArray utf8 = classList.toUtf8( );
	qint64 utfCount = utf8.size( );
	auto type_name_date = utf8.data( );
	type_size_t utfCharSize = utfCount * sizeof( type_name_date[ 0 ] );

	type_size_t vectorSize = sizeof( uint8_t ) /* (大小端标识) */ + sizeof( type_size_t ) /* (总体长度:大小端+type_size_t+QMetaObject+append_size) */ + utfCharSize /* (媒体对象) */ + append_size /* (追加的大小) */;

	// 存储访问保存数据下标
	type_size_t index = 0;
	result_data->resize( vectorSize );

	// 配置大小端
	auto beg = isBegEndian( );
	auto dataPtr = result_data->data( );
	dataPtr[ index ] = beg;
	// 存储转换列表
	std_vector< uint8_t > toDataVector;
	// 存储转换列表的起始指针
	uint8_t *sourceDataPtr;
	// 存储转换列表的个数
	type_size_t sourceCount;
	toData( vectorSize, &toDataVector );
	// 偏移下标
	size_t orgIndex = index + 1;
	sourceCount = toDataVector.size( );
	sourceDataPtr = toDataVector.data( );
	for( index = 0; index < sourceCount; ++index )
		dataPtr[ index + orgIndex ] = sourceDataPtr[ index ];
	orgIndex = index + orgIndex;
	for( index = 0; index < utfCharSize; ++index )
		dataPtr[ index + orgIndex ] = type_name_date[ index ];

	orgIndex = index + orgIndex;
	return dataPtr + orgIndex;
}
uint8_t * ISerialize::converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QMetaObject *meta_object_ptr, const std_vector< QString > &native_type_name, const size_t &append_size ) {
	QStringList stringList;
	size_t count = native_type_name.size( );
	if( count == 0 )
		return converQMetaObjectInfoToUInt8Vector( result_data, meta_object_ptr, stringList, append_size );
	auto data = native_type_name.data( );
	for( size_t index = 0; index < count; ++index )
		stringList.append( data[ index ] );
	return converQMetaObjectInfoToUInt8Vector( result_data, meta_object_ptr, stringList, append_size );
}
uint8_t * ISerialize::converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QObject *meta_object_ptr, const std_vector< QString > &native_type_name, const size_t &append_size ) {
	return converQMetaObjectInfoToUInt8Vector( result_data, meta_object_ptr->metaObject( ), native_type_name, append_size );
}
uint8_t * ISerialize::converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QObject *meta_object_ptr, const QStringList &native_type_name, const size_t &append_size ) {
	return converQMetaObjectInfoToUInt8Vector( result_data, meta_object_ptr->metaObject( ), native_type_name, append_size );
}
uint8_t * ISerialize::converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QMetaObject *meta_object_ptr, const size_t &append_size ) {
	return converQMetaObjectInfoToUInt8Vector( result_data, meta_object_ptr, QStringList { }, append_size );
}
uint8_t * ISerialize::converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QObject *meta_object_ptr, const size_t &append_size ) {
	return converQMetaObjectInfoToUInt8Vector( result_data, meta_object_ptr->metaObject( ), QStringList { }, append_size );
}
uint8_t ISerialize::isBegEndian( ) {
	static union {
		uint32_t i;
		char c[ 4 ];
	} bint = { 0x01020304 };
	return bint.c[ 0 ] == 1;
}
void ISerialize::converEndian( uint8_t *ptr, uint64_t size ) {
	if( size == 0 || size == 1 )
		return;
	if( size == 2 ) {
		uint8_t temp = ptr[ 0 ];
		ptr[ 0 ] = ptr[ 1 ];
		ptr[ 1 ] = temp;
	} else if( size == 4 ) {
		uint8_t temp = ptr[ 0 ];
		ptr[ 0 ] = ptr[ 3 ];
		ptr[ 3 ] = temp;

		temp = ptr[ 1 ];
		ptr[ 1 ] = ptr[ 2 ];
		ptr[ 2 ] = temp;
	} else if( size == 6 ) {
		uint8_t temp = ptr[ 0 ];
		ptr[ 0 ] = ptr[ 5 ];
		ptr[ 5 ] = temp;

		temp = ptr[ 1 ];
		ptr[ 1 ] = ptr[ 4 ];
		ptr[ 4 ] = temp;

		temp = ptr[ 2 ];
		ptr[ 2 ] = ptr[ 3 ];
		ptr[ 3 ] = temp;
	} else if( size == 8 ) {
		uint8_t temp = ptr[ 0 ];
		ptr[ 0 ] = ptr[ 7 ];
		ptr[ 7 ] = temp;

		temp = ptr[ 1 ];
		ptr[ 1 ] = ptr[ 6 ];
		ptr[ 6 ] = temp;

		temp = ptr[ 2 ];
		ptr[ 2 ] = ptr[ 5 ];
		ptr[ 5 ] = temp;

		temp = ptr[ 3 ];
		ptr[ 3 ] = ptr[ 4 ];
		ptr[ 4 ] = temp;
	} else {
		uint8_t temp;
		--size;
		for( uint64_t index = 0; index < size; index++, --size ) {
			temp = ptr[ index ];
			ptr[ index ] = ptr[ size ];
			ptr[ size ] = temp;
		}
	}
}
