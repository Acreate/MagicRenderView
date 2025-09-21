#include "./uint64Serialization.h"


size_t UInt64Serialization::fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t UInt64Serialization::fillObj( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
size_t UInt64Serialization::fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t UInt64Serialization::fillObj( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
size_t UInt64Serialization::fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t UInt64Serialization::fillObj( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
