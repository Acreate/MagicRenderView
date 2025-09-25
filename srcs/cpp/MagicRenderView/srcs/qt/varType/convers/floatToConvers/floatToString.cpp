#include "./floatToString.h"

#include <QList>
#include <cstdint>

#include "../../I_Type.h"

#include "../../../generate/varGenerate.h"
bool FloatToString::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto string = isType< QString >( left_type_info, left );
	if( string == nullptr )
		return false;
	auto call = [string] ( auto *p ) {
		*string = QString::number( *p );
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;

	return false;
}

bool FloatToString::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto string = isType< QString >( left_type_info, left );
	if( string == nullptr )
		return false;
	auto call = [string] ( auto *p ) {
		*string += QString::number( *p );
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;

	return false;
}
bool FloatToString::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto string = isType< QString >( left_type_info, left );
	if( string == nullptr )
		return false;
	auto call = [string] ( auto *p ) {
		QString number = QString::number( *p );
		if( string->endsWith( number ) == false )
			return true;
		*string = string->mid( 0, string->size( ) - number.size( ) );
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;

	return false;
}
bool FloatToString::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto call = [ left_type_info, left] ( auto *p ) {
		int64_t count = *p;
		I_Type type( typeid( int64_t ) );
		return VarGenerate::mul( left_type_info, left, &type, &count );
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;

	return false;
}
bool FloatToString::divTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	auto call = [ left_type_info, left] ( auto *p ) {
		int64_t count = *p;
		I_Type type( typeid( int64_t ) );
		return VarGenerate::div( left_type_info, left, &type, &count );
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;

	return false;
}
bool FloatToString::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {

		QString var = QString::number( *p );
		*result_bool = *leftVar == var;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
		
	return false;
}
bool FloatToString::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {

		QString var = QString::number( *p );
		*result_bool = *leftVar >= var;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
		
	return false;
}
bool FloatToString::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {

		QString var = QString::number( *p );
		*result_bool = *leftVar > var;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
		
	return false;
}
bool FloatToString::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {

		QString var = QString::number( *p );
		*result_bool = *leftVar <= var;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
		
	return false;
}
bool FloatToString::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< QString >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [leftVar, result_bool] ( auto *p ) {

		QString var = QString::number( *p );
		*result_bool = *leftVar < var;
		return true;
	};
	if( typeCall< double >( right_type_info, right, call ) )
		return true;
	if( typeCall< float >( right_type_info, right, call ) )
		return true;
		
	return false;
}
