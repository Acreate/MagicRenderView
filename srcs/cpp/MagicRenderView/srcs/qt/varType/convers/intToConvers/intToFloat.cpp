#include "./intToFloat.h"

#include <QString>
#include <cstdint>

#include "../../I_Type.h"

bool IntToFloat::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	ChackNeedType( double, doubelVar, int64_t, intVar );
	*doubelVar = *intVar;
	return true;
}
bool IntToFloat::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( double, doubelVar, int64_t, intVar );
	*doubelVar += *intVar;
	return true;
}
bool IntToFloat::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( double, doubelVar, int64_t, intVar );
	*doubelVar -= *intVar;
	return true;
}
bool IntToFloat::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( double, doubelVar, int64_t, intVar );
	*doubelVar *= *intVar;
	return true;
}
bool IntToFloat::devTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( double, doubelVar, int64_t, intVar );
	*doubelVar /= *intVar;
	return true;
}
