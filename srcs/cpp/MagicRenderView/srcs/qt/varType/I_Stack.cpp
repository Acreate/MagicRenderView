#include "I_Stack.h"

#include "../application/application.h"
I_Stack::I_Stack( const type_info &generate_type_info ) : generateTypeInfo( generate_type_info ) {
	this->varGenerate = Application::getApplicationInstancePtr( )->getVarGenerate( );
}
bool I_Stack::getPtrTypeInfo( const void *check_var_ptr, const type_info *&result_type ) const {
	size_t count = stackVarPtr.size( );
	if( count == 0 )
		return false;
	auto data = stackVarPtr.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == check_var_ptr ) {
			result_type = &generateTypeInfo;
			return true;
		}
	return false;
}
size_t I_Stack::fillBinVector( const void *source_data_ptr, const size_t &source_ptr_count, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
	result_mirror_image_bin_vector.resize( source_ptr_count );
	auto pasteTargetDataPtr = result_mirror_image_bin_vector.data( );
	auto copyTargetDataPtr = ( const uint8_t * ) source_data_ptr;
	for( size_t index = 0; index < source_ptr_count; ++index )
		pasteTargetDataPtr[ index ] = copyTargetDataPtr[ index ];
	return source_ptr_count;
}
size_t I_Stack::fillBinVector( const QString &var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	std_vector< uint8_t > buff;
	auto byteArray = var_type.toUtf8( );
	fillBinVector( byteArray.data( ), byteArray.size( ), buff );
	size_t buffCount = buff.size( );
	fillBinVector( &buffCount, sizeof( size_t ), result_bin_data_vector );
	result_bin_data_vector.append_range( buff );
	return result_bin_data_vector.size( );
}
size_t I_Stack::fillObjVector( void *target_var_ptr, const size_t &target_need_count, const uint8_t *source_data_ptr, const size_t &source_ptr_count ) const {
	if( target_need_count > source_ptr_count )
		return 0;
	memcpy( target_var_ptr, source_data_ptr, target_need_count );
	return target_need_count;
}
size_t I_Stack::fillObjVector( QString *target_var_ptr, const uint8_t *source_data_ptr, const size_t &source_ptr_count ) const {
	size_t count;
	auto add = fillObjVector( &count, sizeof( size_t ), source_data_ptr, source_ptr_count );
	const char *sourcePtr = ( const char * ) source_data_ptr + add;
	if( count > ( source_ptr_count - add ) )
		return 0;
	QByteArray array( sourcePtr, count );
	*target_var_ptr = QString::fromUtf8( array );
	return count + add;
}
