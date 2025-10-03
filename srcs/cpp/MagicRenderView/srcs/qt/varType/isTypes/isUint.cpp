#include "isUint.h"
bool IsUint::isInt( const type_info &check_type_info, void *check_type_data_ptr ) const {
	isType( uint8_t, check_type_info );
	isType( uint16_t, check_type_info );
	isType( uint32_t, check_type_info );
	isType( uint64_t, check_type_info );
	return false;
}
bool IsUint::isUInt( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsUint::isFloat( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsUint::isString( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsUint::getTypeName( const type_info &check_type_info, void *check_type_data_ptr, QString &result_type_string_name ) const {
	isTypeResultName( uint8_t, check_type_info, result_type_string_name );
	isTypeResultName( uint16_t, check_type_info, result_type_string_name );
	isTypeResultName( uint32_t, check_type_info, result_type_string_name );
	isTypeResultName( uint64_t, check_type_info, result_type_string_name );
	return false;
}
