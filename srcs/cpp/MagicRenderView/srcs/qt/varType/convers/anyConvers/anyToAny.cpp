#include "anyToAny.h"
bool AnyToAny::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return true;
}
bool AnyToAny::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return true;
}
bool AnyToAny::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return I_Conver::subTarget( left_type_info, left, right_type_info, right );
}
bool AnyToAny::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return true;
}
bool AnyToAny::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	return true;
}
bool AnyToAny::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return true;
}
bool AnyToAny::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return true;
}
bool AnyToAny::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return true;
}
bool AnyToAny::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return true;
}
bool AnyToAny::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	return true;
}
bool AnyToAny::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	return true;
}
