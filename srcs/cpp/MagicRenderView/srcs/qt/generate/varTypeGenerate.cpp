#include "./varTypeGenerate.h"
#include <QDebug>

/// @brief 平台是否小端
/// @return true 表示小端
bool VarTypeGenerate::isLittleEndian( ) {
	union {
		int i;
		char c;
	} un;	// 匿名联合体
	un.i = 1;
	// 小端：返回 1，说明数据的低字节在内存的低地址存放
	return un.c == 1;
}
QString VarTypeGenerate::getMetaInfo( const uint8_t *source_data_ptr, const size_t &source_count ) {
	size_t metaCount = *( size_t * ) source_data_ptr;
	size_t sizeSize = sizeof( size_t );
	source_data_ptr += sizeSize;
	QString result;
	toObj( &result, source_data_ptr, metaCount );
	return result;
}
size_t VarTypeGenerate::toVectorUInt8Data( const void *source_ptr, const size_t &source_ptr_count, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	result_mirror_image_bin_vector.resize( source_ptr_count );
	size_t count = result_mirror_image_bin_vector.size( );
	auto pasteTargetDataPtr = result_mirror_image_bin_vector.data( );
	auto copyTargetDataPtr = ( const uint8_t * ) source_ptr;
	for( size_t index = 0; index < source_ptr_count; ++index )
		pasteTargetDataPtr[ index ] = copyTargetDataPtr[ index ];
	return source_ptr_count;
}

size_t VarTypeGenerate::toVectorUInt8Data( const QString &var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	auto byteArray = var_type.toUtf8( );
	return toVectorUInt8Data( byteArray.data( ), byteArray.size( ), result_bin_data_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const uint8_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( &var_type, sizeof uint8_t, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const uint16_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( &var_type, sizeof uint16_t, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const uint32_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( &var_type, sizeof uint32_t, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const uint64_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( &var_type, sizeof uint64_t, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const float_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( &var_type, sizeof float_t, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const double_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( &var_type, sizeof double_t, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const std::string &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	QString fromStdString = QString::fromStdString( var_type );
	return toVectorUInt8Data( fromStdString, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const std::wstring &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	QString fromStdString = QString::fromStdWString( var_type );
	return toVectorUInt8Data( fromStdString, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const int8_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( ( uint8_t ) var_type, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const int16_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( ( const uint16_t ) var_type, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const int32_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( ( const uint32_t ) var_type, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toVectorUInt8Data( const int64_t &var_type, std_vector< uint8_t > &result_mirror_image_bin_vector ) {
	return toVectorUInt8Data( ( const uint64_t ) var_type, result_mirror_image_bin_vector );
}
size_t VarTypeGenerate::toObj( QString *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	const char *sourcePtr = ( const char * ) source_ptr;
	QByteArray array( sourcePtr, source_ptr_count );
	*target_var_ptr = QString::fromUtf8( array );
	return source_ptr_count;
}
size_t VarTypeGenerate::toObj( uint8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( uint8_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}
size_t VarTypeGenerate::toObj( uint16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( uint16_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}
size_t VarTypeGenerate::toObj( uint32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( uint32_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}
size_t VarTypeGenerate::toObj( uint64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( uint64_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}
size_t VarTypeGenerate::toObj( float_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( float_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}
size_t VarTypeGenerate::toObj( double_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( double_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}

size_t VarTypeGenerate::toObj( std::string *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	QString buff;
	auto count = toObj( &buff, source_ptr, source_ptr_count );
	if( count == 0 )
		return 0;
	*target_var_ptr = buff.toStdString( );
	return count;
}

size_t VarTypeGenerate::toObj( std::wstring *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	QString buff;
	auto count = toObj( &buff, source_ptr, source_ptr_count );
	if( count == 0 )
		return 0;
	*target_var_ptr = buff.toStdWString( );
	return count;
}
size_t VarTypeGenerate::toObj( int8_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( int8_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}
size_t VarTypeGenerate::toObj( int16_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( int16_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}
size_t VarTypeGenerate::toObj( int32_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( int32_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}
size_t VarTypeGenerate::toObj( int64_t *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	size_t checkCount = sizeof( int64_t );
	if( checkCount > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_ptr, checkCount );
	return checkCount;
}

std_vector< VarType * > VarTypeGenerate::vars;
VarType * VarTypeGenerate::templateVarType( QObject *parent, const QString &type_name ) {
	VarType *result = new VarType( parent );
	result->unityTypeName = type_name;
	QObject::connect( result, &VarType::deleteObjBefore, [] ( VarType *deleteType ) {
		size_t count = vars.size( );
		auto data = vars.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ] == deleteType )
				data[ index ] = nullptr;
	} );
	size_t count = vars.size( );
	auto data = vars.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == nullptr ) {
			data[ index ] = result;
			result->generateCode = index;
			return result;
		}
	vars.emplace_back( result );
	result->generateCode = count;
	return result;
}
