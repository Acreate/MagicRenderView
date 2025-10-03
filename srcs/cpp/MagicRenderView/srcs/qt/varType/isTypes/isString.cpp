#include "isString.h"
bool IsString::isInt( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsString::isUInt( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsString::isFloat( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsString::isString( const type_info &check_type_info, void *check_type_data_ptr ) const {
	isType( std::string, check_type_info );
	isType( std::wstring, check_type_info );
	isType( QString, check_type_info );
	return false;
}
bool IsString::getTypeName( const type_info &check_type_info, void *check_type_data_ptr, QString &result_type_string_name ) const {
	isTypeResultName( std::string, check_type_info, result_type_string_name );
	isTypeResultName( std::wstring, check_type_info, result_type_string_name );
	isTypeResultName( QString, check_type_info, result_type_string_name );
	return false;
}
