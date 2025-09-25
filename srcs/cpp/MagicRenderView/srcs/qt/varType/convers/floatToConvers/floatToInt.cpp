#include "./floatToInt.h"

#include <cstdint>

#include "../../I_Type.h"
bool FloatToInt::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *p ) {
		*leftVar = *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;

	return false;
}
bool FloatToInt::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *p ) {
		*leftVar += *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
	return false;
}
bool FloatToInt::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *p ) {
		*leftVar -= *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
	return false;
}
bool FloatToInt::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *p ) {
		*leftVar *= *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
	return false;
}
bool FloatToInt::divTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar] ( auto *p ) {
		if( *p != 0 )
			*leftVar /= *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
	return false;
}
bool FloatToInt::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {
		*result_bool = *leftVar == *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
	return false;
}
bool FloatToInt::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {
		*result_bool = *leftVar >= *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
	return false;
}
bool FloatToInt::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {
		*result_bool = *leftVar > *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
	return false;
}
bool FloatToInt::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {
		*result_bool = *leftVar <= *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
	return false;
}
bool FloatToInt::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {
		*result_bool = *leftVar < *p;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
	return false;
}
