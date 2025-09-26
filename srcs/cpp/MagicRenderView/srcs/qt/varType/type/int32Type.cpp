#include "int32Type.h"
bool Int32Type::createTarget( const type_info &target_type_info, const std_function<void(void *create_obj_ptr)> &create_call_function ) {
	return I_Stack::createTarget( target_type_info, create_call_function );
}
bool Int32Type::deleteTarget( const type_info &target_type_info, void *target_ptr ) {
	return I_Stack::deleteTarget( target_type_info, target_ptr );
}
bool Int32Type::deleteTarget( void *target_ptr ) {
	return I_Stack::deleteTarget( target_ptr );
}
bool Int32Type::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector<uint8_t> &result_vector, size_t &result_count ) {
	return I_Stack::toBinVector( target_type_info, target_ptr, result_vector, result_count );
}
bool Int32Type::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) {
	return false;
}
