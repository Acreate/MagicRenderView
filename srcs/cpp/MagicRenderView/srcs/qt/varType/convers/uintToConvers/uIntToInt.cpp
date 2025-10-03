#include "uIntToInt.h"

#include "../../../generate/varGenerate.h"
bool UIntToInt::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::fillTarget( left_type_info, left, right_type_info, right );
}
bool UIntToInt::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::addTarget( left_type_info, left, right_type_info, right );
}
bool UIntToInt::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::subTarget( left_type_info, left, right_type_info, right );
}
bool UIntToInt::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::mulTarget( left_type_info, left, right_type_info, right );
}
bool UIntToInt::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::divTarget( left_type_info, left, right_type_info, right );
}
bool UIntToInt::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::equThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool UIntToInt::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool UIntToInt::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool UIntToInt::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool UIntToInt::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool UIntToInt::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( varGenerate->isInt( left_type_info, nullptr ) && varGenerate->isUInt( right_type_info, nullptr ) )
		return true;
	return false;
}
