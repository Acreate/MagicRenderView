#include "./floatToString.h"

#include <QList>
#include <cstdint>

#include "../../I_Type.h"
bool FloatToString::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}

bool FloatToString::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool FloatToString::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool FloatToString::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return true;
}
bool FloatToString::divTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
