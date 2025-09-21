#include "./nodeItemSerialization.h"
NodeItemSerialization::NodeItemSerialization( ) {
	auto &typeInfo = typeid( t_current_type );
	typeName = typeInfo.name( );
}
size_t NodeItemSerialization::fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return 0;
}
size_t NodeItemSerialization::fillObj( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	return 0;
}
size_t NodeItemSerialization::fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return 0;
}
size_t NodeItemSerialization::fillObj( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	return 0;
}
size_t NodeItemSerialization::fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return 0;
}
size_t NodeItemSerialization::fillObj( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	return 0;
}
