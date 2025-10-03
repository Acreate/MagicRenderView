#include "isFloat.h"
bool IsFloat::isInt( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsFloat::isUInt( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsFloat::isFloat( const type_info &check_type_info, void *check_type_data_ptr ) const {
	isType( float, check_type_info );
	isType( double, check_type_info );
	return false;
}
bool IsFloat::isString( const type_info &check_type_info, void *check_type_data_ptr ) const {
	return false;
}
bool IsFloat::getTypeName( const type_info &check_type_info, void *check_type_data_ptr, QString &result_type_string_name ) const {
	isTypeResultName( float, check_type_info, result_type_string_name );
	isTypeResultName( double, check_type_info, result_type_string_name );
	return false;

}
