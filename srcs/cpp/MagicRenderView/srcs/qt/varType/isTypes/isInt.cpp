#include "isInt.h"


bool IsInt::isInt( const type_info &check_type_info, void *check_type_data_ptr ) const {
	isType( int8_t, check_type_info );
	isType( int16_t, check_type_info );
	isType( int32_t, check_type_info );
	isType( int64_t, check_type_info );

	return false;
}
bool IsInt::isUInt( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsInt::isFloat( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsInt::isString( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsInt::getTypeName( const type_info &check_type_info, void *check_type_data_ptr, QString &result_type_string_name ) const {
	isTypeResultName( int8_t, check_type_info, result_type_string_name );
	isTypeResultName( int16_t, check_type_info, result_type_string_name );
	isTypeResultName( int32_t, check_type_info, result_type_string_name );
	isTypeResultName( int64_t, check_type_info, result_type_string_name );
	return false;
}
