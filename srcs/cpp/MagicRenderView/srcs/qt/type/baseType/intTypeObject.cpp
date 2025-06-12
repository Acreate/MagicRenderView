#include "intTypeObject.h"
size_t IntTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) const {
	return ITypeObject::serializeToObjectData( read_data_vector, data_count );
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
	// 所有数据的长度 = 类型+统计类型+对象值+大小端
	type_size_t dataCount = utf8.size( ) + sizeof( type_size_t ) + sizeof( val ) + sizeof( uint8_t );
	// 存储访问保存数据下标
	type_size_t  index = 0;
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
	sourceCount = toDataVector.size( );
	sourceDataPtr = toDataVector.data( );
	for()
	dataPtr[ index ] = beg;

		return dataCount;
}
