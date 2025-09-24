#include "./intToFloat.h"

#include <QString>
#include <cstdint>

#include "../../I_Type.h"

bool IntToFloat::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;
	bool isOk = typeCall< int8_t >(
		right_type_info, right,
		[doubelVar] ( int8_t *var ) {
			*doubelVar = *var;
			return true;
		} );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >(
		right_type_info, right,
		[doubelVar] ( auto *var ) {
			*doubelVar = *var;
			return true;
		} );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >(
		right_type_info, right,
		[doubelVar] ( auto *var ) {
			*doubelVar = *var;
			return true;
		} );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >(
		right_type_info, right,
		[doubelVar] ( auto *var ) {
			*doubelVar = *var;
			return true;
		} );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >(
		right_type_info, right,
		[doubelVar] ( auto *var ) {
			*doubelVar = *var;
			return true;
		} );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >(
		right_type_info, right,
		[doubelVar] ( auto *var ) {
			*doubelVar = *var;
			return true;
		} );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >(
		right_type_info, right,
		[doubelVar] ( auto *var ) {
			*doubelVar = *var;
			return true;
		} );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >(
		right_type_info, right,
		[doubelVar] ( auto *var ) {
			*doubelVar = *var;
			return true;
		} );
	if( isOk )
		return true;
	
	return false;
}
bool IntToFloat::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool IntToFloat::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool IntToFloat::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool IntToFloat::devTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	return false;
}
bool IntToFloat::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::equThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool IntToFloat::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool IntToFloat::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::greaterThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool IntToFloat::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
bool IntToFloat::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	return I_Conver::lessThanTarget( left_type_info, left, right_type_info, right, result_bool );
}
