#include "./stringToFloat.h"

#include "../../I_Type.h"

#include "../../../generate/varGenerate.h"
bool StringToFloat::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto call = [this,&left_type_info,left] ( auto *string ) {
		bool isOK = fillFloat( string, left, left_type_info );
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		double result = 0;
		bool isOK = fillFloat( string, &result, typeid( double ) );
		if( isOK )
			*leftVar += result;
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		double result = 0;
		bool isOK = fillFloat( string, &result, typeid( double ) );
		if( isOK )
			*leftVar -= result;
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		double result = 0;
		bool isOK = fillFloat( string, &result, typeid( double ) );
		if( isOK )
			*leftVar *= result;
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		double result = 0;
		bool isOK = fillFloat( string, &result, typeid( double ) );
		if( isOK && result != 0 )
			*leftVar /= result;
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillFloat( string, &result, typeid( double ) );
		*result_bool = *leftVar == result;
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillFloat( string, &result, typeid( double ) );
		*result_bool = *leftVar >= result;
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillFloat( string, &result, typeid( double ) );
		*result_bool = *leftVar > result;
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillFloat( string, &result, typeid( double ) );
		*result_bool = *leftVar <= result;
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillFloat( string, &result, typeid( double ) );
		*result_bool = *leftVar < result;
		return isOK;
	};
	bool typeCallResult = typeCall< QString >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::string >( right_type_info, right, call );
	if( typeCallResult )
		return true;
	typeCallResult = typeCall< std::wstring >( right_type_info, right, call );
	if( typeCallResult )
		return true;

	return false;
}
bool StringToFloat::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	if( varGenerate->isFloat( left_type_info, nullptr ) && varGenerate->isString( right_type_info, nullptr ) )
		return true;
	return false;
}
