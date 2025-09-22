#include "./stdStringSerialization.h"

size_t StdStringSerialization::fillUnityBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return serialization.fillUnityBin< t_current_type >( this, var_type, result_bin_data_vector );
}
size_t StdStringSerialization::fillUnityObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return serialization.fillUnityObj< t_current_type >( this, var_type, source_ptr, source_ptr_count );
}
size_t StdStringSerialization::fillVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return serialization.fillVectorBin< t_current_type >( this, var_type, result_bin_data_vector );
}
size_t StdStringSerialization::fillVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return serialization.fillVectorObj< t_current_type >( this, var_type, source_ptr, source_ptr_count );
}
size_t StdStringSerialization::fillPtrVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return serialization.fillPtrVectorBin< t_current_type >( this, var_type, result_bin_data_vector );
}
size_t StdStringSerialization::fillPtrVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return serialization.fillPtrVectorObj< t_current_type >( this, var_type, source_ptr, source_ptr_count );
}
bool StdStringSerialization::getNewObj( void **new_set_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	*new_set_ptr = new t_current_type;
	return true;
}
bool StdStringSerialization::removeNewObj( void *new_set_ptr ) {
	delete ( t_current_type * ) new_set_ptr;
	return false;
}
