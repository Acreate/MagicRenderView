#include "./qstringSerialization.h"


size_t QStringSerialization::fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t QStringSerialization::fillObj( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
size_t QStringSerialization::fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t QStringSerialization::fillObj( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
size_t QStringSerialization::fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t QStringSerialization::fillObj( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
