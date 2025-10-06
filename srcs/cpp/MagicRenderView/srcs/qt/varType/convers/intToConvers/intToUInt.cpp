#include "intToUInt.h"

#include "../../../generate/varGenerate.h"
bool IntToUInt::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::fillTarget( left_type_info, left, right_type_info, right );
}
bool IntToUInt::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::addTarget( left_type_info, left, right_type_info, right );
}
bool IntToUInt::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::subTarget( left_type_info, left, right_type_info, right );
}
bool IntToUInt::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::mulTarget( left_type_info, left, right_type_info, right );
}
bool IntToUInt::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::divTarget( left_type_info, left, right_type_info, right );
}
bool IntToUInt::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::equThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool IntToUInt::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool IntToUInt::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool IntToUInt::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool IntToUInt::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool IntToUInt::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( I_Type::isUInt( left_type_info ) && I_Type::isInt( right_type_info ) )
		return true;
	return false;
}
