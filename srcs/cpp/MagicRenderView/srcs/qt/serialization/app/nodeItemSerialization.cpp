#include "./nodeItemSerialization.h"
#include <qt/node/item/nodeItem.h>
#include <qt/node/prot/NodePort.h>
NodeItemSerialization::NodeItemSerialization( ) {
	auto &typeInfo = typeid( t_current_type );
	typeName = typeInfo.name( );
}
size_t NodeItemSerialization::fillUnityBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return 0;
}
size_t NodeItemSerialization::fillUnityObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return 0;
}
size_t NodeItemSerialization::fillVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return 0;
}
size_t NodeItemSerialization::fillVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return 0;
}
size_t NodeItemSerialization::fillPtrVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return 0;
}
size_t NodeItemSerialization::fillPtrVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return 0;
}
bool NodeItemSerialization::getNewObj( void **new_set_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return false;
}
bool NodeItemSerialization::removeNewObj( void *new_set_ptr ) {
	return false;
}
