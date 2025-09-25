#include "floatToFloat.h"

#include "../../I_Type.h"
bool FloatToFloat::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
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
bool FloatToFloat::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
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
bool FloatToFloat::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
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
bool FloatToFloat::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
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
bool FloatToFloat::divTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
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
bool FloatToFloat::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
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
bool FloatToFloat::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
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
bool FloatToFloat::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
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
bool FloatToFloat::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
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
bool FloatToFloat::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
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
