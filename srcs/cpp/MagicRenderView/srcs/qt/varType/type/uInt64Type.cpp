#include "uInt64Type.h"
bool UInt64Type::createTarget( const type_info &target_type_info, void *&target_ptr ) {
	return I_Stack::createTarget( target_type_info, target_ptr );
}
bool UInt64Type::deleteTarget( const type_info &target_type_info, void *target_ptr ) {
	return I_Stack::deleteTarget( target_type_info, target_ptr );
}
bool UInt64Type::deleteTarget( void *target_ptr ) {
	return I_Stack::deleteTarget( target_ptr );
}
bool UInt64Type::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector<uint8_t> &result_vector, size_t &result_count ) {
	return I_Stack::toBinVector( target_type_info, target_ptr, result_vector, result_count );
}
bool UInt64Type::toOBjVector( const type_info &target_type_info, void *&target_ptr, size_t &result_count, const std_vector<uint8_t> &load_bin_vector ) {
	return I_Stack::toOBjVector( target_type_info, target_ptr, result_count, load_bin_vector );
}
