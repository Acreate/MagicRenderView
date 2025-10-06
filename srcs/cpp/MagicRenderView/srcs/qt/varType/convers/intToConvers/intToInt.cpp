#include "intToInt.h"

#include "../../../generate/varGenerate.h"
bool IntToInt::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *string ) {
		*leftVar = *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *string ) {
		*leftVar += *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *string ) {
		*leftVar -= *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *string ) {
		*leftVar *= *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *string ) {
		if( *string != 0 )
			*leftVar /= *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *string ) {
		*result_bool = *leftVar == *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *string ) {
		*result_bool = *leftVar <= *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *string ) {
		*result_bool = *leftVar < *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *string ) {
		*result_bool = *leftVar >= *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *string ) {
		*result_bool = *leftVar > *string;
		return true;
	};
	bool runResult;
	runResult = typeCall< int64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint64_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint32_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint8_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< int16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	runResult = typeCall< uint16_t >( right_type_info, right, call );
	if( runResult )
		return true;
	return false;
}
bool IntToInt::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( I_Type::isInt( left_type_info ) && I_Type::isInt( right_type_info ) )
		return true;
	return false;
}
