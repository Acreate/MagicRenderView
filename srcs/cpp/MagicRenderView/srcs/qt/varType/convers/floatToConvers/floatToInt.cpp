#include "./floatToInt.h"

#include <cstdint>

#include "../../I_Type.h"
bool FloatToInt::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	ChackNeedType( int64_t, intVar, double, doubelVar );
	*intVar = *doubelVar;
	return true;
}
bool FloatToInt::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( int64_t, intVar, double, doubelVar );
	*intVar += *doubelVar;
	return true;
}
bool FloatToInt::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( int64_t, intVar, double, doubelVar );
	*intVar -= *doubelVar;
	return true;
}
bool FloatToInt::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( int64_t, intVar, double, doubelVar );
	*intVar *= *doubelVar;
	return true;
}
bool FloatToInt::devTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( int64_t, intVar, double, doubelVar );
	*intVar /= *doubelVar;
	return true;
}
