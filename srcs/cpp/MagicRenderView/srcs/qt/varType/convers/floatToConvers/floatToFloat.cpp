#include "floatToFloat.h"

#include "../../I_Type.h"
bool FloatToFloat::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToFloat::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToFloat::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToFloat::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToFloat::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

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
bool FloatToFloat::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
bool FloatToFloat::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
bool FloatToFloat::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
bool FloatToFloat::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
bool FloatToFloat::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

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
