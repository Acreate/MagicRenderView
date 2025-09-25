#include "./floatToInt.h"

#include <cstdint>

#include "../../I_Type.h"
bool FloatToInt::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {


	return false;
}
bool FloatToInt::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool FloatToInt::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool FloatToInt::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool FloatToInt::divTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool FloatToInt::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::equThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool FloatToInt::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool FloatToInt::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool FloatToInt::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool FloatToInt::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
