#include "./int32Serialization.h"

size_t Int32Serialization::fillUnityBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return serialization.fillUnityBin< t_current_type >( this, var_type, result_bin_data_vector );
}
size_t Int32Serialization::fillUnityObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return serialization.fillUnityObj< t_current_type >( this, var_type, source_ptr, source_ptr_count );
}
size_t Int32Serialization::fillVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return serialization.fillVectorBin< t_current_type >( this, var_type, result_bin_data_vector );
}
size_t Int32Serialization::fillVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return serialization.fillVectorObj< t_current_type >( this, var_type, source_ptr, source_ptr_count );
}
size_t Int32Serialization::fillPtrVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return serialization.fillPtrVectorBin< t_current_type >( this, var_type, result_bin_data_vector );
}
size_t Int32Serialization::fillPtrVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return serialization.fillPtrVectorObj< t_current_type >( this, var_type, source_ptr, source_ptr_count );
}
bool Int32Serialization::getNewObj( void **new_set_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	*new_set_ptr = new t_current_type;
	return true;
}
bool Int32Serialization::removeNewObj( void *new_set_ptr ) {
	delete ( t_current_type * ) new_set_ptr;
	return true;
}
