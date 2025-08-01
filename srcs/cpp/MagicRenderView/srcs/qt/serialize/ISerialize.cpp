﻿#include "./ISerialize.h"
#include <qt/types/ITypeObject.h>
#include <QList>

ISerialize::SerializeInfo::SerializeInfo( const uint8_t *data_ptr, const size_t &data_size ): data( data_size ) {
	isInitTrue = false;
	auto dataPtr = data.data( );
	for( size_t index = 0; index < data_size; ++index )
		dataPtr[ index ] = data_ptr[ index ];
}
bool ISerialize::SerializeInfo::init( ) {
	infoLastPtr = getSerializeInfo( data.data( ), data.size( ), &begEndian, &stackNames, &metaObjectClassNames, &typeNames );
	// 配置数据起始地址
	return infoLastPtr;
}

ISerialize::type_size_t ISerialize::SerializeInfo::getSerializeInfo( const uint8_t *data_ptr, const size_t &data_size, uint8_t *result_is_beg_endian, std_vector< QString > *result_stack_type_name, std_vector< QString > *result_qt_meta_names, std_vector< QString > *result_obj_type_names ) {
	auto dataPtr = data_ptr;
	size_t dataCount = data_size;
	// 获取大小端
	*result_is_beg_endian = *dataPtr;
	uchar endian = ISerialize::isBegEndian( );
	auto size = *( type_size_t * ) ( dataPtr + 1 );
	if( *result_is_beg_endian != endian )
		converEndian( size );
	if( size > dataCount ) {
		tools::debug::printError( "数据是损坏的" );
		return 0;
	}
	// 找到类型
	dataPtr = dataPtr + 1 + sizeof( type_size_t );
	auto stringInfoSize = *( size_t * ) dataPtr;
	dataPtr += sizeof( type_size_t );
	QByteArray hex;
	hex.resize( stringInfoSize );
	auto hexDataPtr = hex.data( );
	for( size_t index = 0; index < stringInfoSize; ++index )
		hexDataPtr[ index ] = dataPtr[ index ];
	// 找到 [ 
	QString structString( hex );
	QString mid;
	QStringList stringList;
	qsizetype left;
	qsizetype right;
	left = structString.indexOf( "[" );
	if( result_stack_type_name ) {
		result_stack_type_name->clear( );
		for( auto &type : structString.mid( 0, left - 1 ).split( "," ) )
			result_stack_type_name->emplace_back( type );
	}
	// 找到 ]
	right = structString.indexOf( "]", left );
	if( result_obj_type_names ) {
		mid = structString.mid( left, right - left );
		stringList = mid.split( "," );
		result_obj_type_names->clear( );
		for( auto &unityString : stringList )
			result_obj_type_names->emplace_back( QByteArray::fromHex( unityString.toUtf8( ) ) );
	}
	// 找到 {}
	if( result_qt_meta_names ) {
		left = structString.indexOf( "{", right );
		right = structString.indexOf( "}", left );
		mid = structString.mid( left, right - left );
		stringList = mid.split( "," );
		result_qt_meta_names->clear( );
		for( auto &unityString : stringList )
			result_qt_meta_names->emplace_back( QByteArray::fromHex( unityString.toUtf8( ) ) );
	}
	return stringInfoSize + 1 + sizeof( type_size_t ) * 2;
}
std_vector< QString > ISerialize::SerializeInfo::getMetaInheritInfo( const QMetaObject *meta_object_ptr ) {
	std_vector< QString > result;
	QString className = meta_object_ptr->className( );
	result.emplace_back( className );
	do {
		meta_object_ptr = meta_object_ptr->superClass( );
		if( meta_object_ptr == nullptr )
			break;
		className = meta_object_ptr->className( );
		result.emplace_back( className );
	} while( true );
	return result;
}
uint8_t * ISerialize::converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QMetaObject *meta_object_ptr, const QString &stack_type_name, const QStringList &native_type_name, const size_t &append_size ) {
	QStringList classNameList;

	for( auto &str : native_type_name )
		classNameList.append( str.toUtf8( ).toHex( ) );

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

	auto stackTypeName = stack_type_name + "]:{" + classNameList.join( "," ) + "}";
	QByteArray utf8 = stackTypeName.toUtf8( );
	qint64 utfCount = utf8.size( );
	auto type_name_date = utf8.data( );
	type_size_t utfCharSize = utfCount * sizeof( type_name_date[ 0 ] );

	// 配置大小端
	auto beg = isBegEndian( );
	type_size_t vectorSize = sizeof( beg ) /* (大小端标识) */ + sizeof( utfCharSize ) /* (总体长度:大小端+type_size_t+QMetaObject+append_size) */ + sizeof( vectorSize ) /* (字符串信息大小) */ + utfCharSize /* (媒体对象) */ + append_size /* (追加的大小) */;

	// 存储访问保存数据下标
	type_size_t index = 0;
	result_data->resize( vectorSize );

	auto dataPtr = result_data->data( );
	// 大小端
	dataPtr[ index ] = beg;
	// 存储转换列表
	std_vector< uint8_t > toDataVector;
	// 存储转换列表的起始指针
	uint8_t *sourceDataPtr;
	// 存储转换列表的个数
	type_size_t sourceCount;
	toData( vectorSize, &toDataVector );
	// 偏移下标
	sourceCount = toDataVector.size( );
	sourceDataPtr = toDataVector.data( );
	// 总大小
	dataPtr += 1;
	for( index = 0; index < sourceCount; ++index )
		dataPtr[ index ] = sourceDataPtr[ index ];
	// 字符串大小
	toData( utfCharSize, &toDataVector );
	sourceDataPtr = toDataVector.data( );
	sourceCount = toDataVector.size( );
	dataPtr += index;
	for( index = 0; index < sourceCount; ++index )
		dataPtr[ index ] = sourceDataPtr[ index ];
	// 字符串信息
	dataPtr += index;
	for( index = 0; index < utfCharSize; ++index )
		dataPtr[ index ] = type_name_date[ index ];
	dataPtr += index;
	return dataPtr;
}
uint8_t * ISerialize::converQMetaObjectInfoToUInt8Vector( std_vector< uint8_t > *result_data, const QMetaObject *meta_object_ptr, const QString &stack_type_name, const std_vector< QString > &native_type_name, const size_t &append_size ) {
	QStringList nativeTypeList, stackTypeList;
	size_t count = native_type_name.size( );
	auto data = native_type_name.data( );
	for( size_t index = 0; index < count; ++index )
		nativeTypeList.append( data[ index ] );

	return converQMetaObjectInfoToUInt8Vector( result_data, meta_object_ptr, stack_type_name, nativeTypeList, append_size );
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
