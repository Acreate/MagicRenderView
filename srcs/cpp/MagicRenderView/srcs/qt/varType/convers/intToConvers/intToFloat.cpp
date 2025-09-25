#include "./intToFloat.h"

#include <QString>
#include <cstdint>

#include "../../I_Type.h"

bool IntToFloat::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;
	auto call = [doubelVar] ( auto *var ) {
		*doubelVar = *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	return false;
}
bool IntToFloat::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;
	auto call = [doubelVar] ( auto *var ) {
		*doubelVar += *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	return false;
}
bool IntToFloat::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;

	auto call = [doubelVar] ( auto *var ) {
		*doubelVar -= *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	return false;
}
bool IntToFloat::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;

	auto call = [doubelVar] ( auto *var ) {
		*doubelVar *= *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	return false;
}
bool IntToFloat::divTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;

	auto call = [doubelVar] ( auto *var ) {
		if( *var != 0 )
			*doubelVar /= *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToFloat::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;

	auto call = [doubelVar, result_bool] ( auto *var ) {
		*result_bool = *doubelVar == *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	return false;
}
bool IntToFloat::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;

	auto call = [doubelVar, result_bool] ( auto *var ) {
		*result_bool = *doubelVar >= *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	return false;
}
bool IntToFloat::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;

	auto call = [doubelVar, result_bool] ( auto *var ) {
		*result_bool = *doubelVar > *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	return false;
}
bool IntToFloat::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;

	auto call = [doubelVar, result_bool] ( auto *var ) {
		*result_bool = *doubelVar <= *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToFloat::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto doubelVar = isType< double >( left_type_info, left );
	if( doubelVar == nullptr )
		return false;

	auto call = [doubelVar, result_bool] ( auto *var ) {
		*result_bool = *doubelVar < *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
