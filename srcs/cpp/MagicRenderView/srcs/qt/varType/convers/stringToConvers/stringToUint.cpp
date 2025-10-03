#include "stringToUint.h"

#include "../../../generate/varGenerate.h"
bool StringToUint::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::fillTarget( left_type_info, left, right_type_info, right );
}
bool StringToUint::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::addTarget( left_type_info, left, right_type_info, right );
}
bool StringToUint::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::subTarget( left_type_info, left, right_type_info, right );
}
bool StringToUint::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::mulTarget( left_type_info, left, right_type_info, right );
}
bool StringToUint::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::divTarget( left_type_info, left, right_type_info, right );
}
bool StringToUint::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::equThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool StringToUint::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool StringToUint::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool StringToUint::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool StringToUint::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool StringToUint::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {

	if( varGenerate->isUInt( left_type_info, nullptr ) && varGenerate->isString( right_type_info, nullptr ) )
		return true;
	return false;
}
