#include "./floatToInt.h"

#include <cstdint>

#include "../../I_Type.h"

#include "../../../generate/varGenerate.h"
bool FloatToInt::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToInt::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToInt::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToInt::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToInt::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToInt::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
bool FloatToInt::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
bool FloatToInt::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
bool FloatToInt::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
bool FloatToInt::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
bool FloatToInt::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( I_Type::isInt( left_type_info ) && I_Type::isFloat( right_type_info ) )
		return true;
	return false;
}
