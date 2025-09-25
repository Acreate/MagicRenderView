#include "./stringToFloat.h"

#include "../../I_Type.h"
bool StringToFloat::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto call = [this,left_type_info,left] ( auto *string ) {
		const type_info &targetTypeInfo = left_type_info->getTypeInfo( );
		bool isOK = fillInt( string, left, targetTypeInfo );
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
bool StringToFloat::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		double result = 0;
		bool isOK = fillInt( string, &result, typeid( double ) );
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
bool StringToFloat::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		double result = 0;
		bool isOK = fillInt( string, &result, typeid( double ) );
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
bool StringToFloat::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		double result = 0;
		bool isOK = fillInt( string, &result, typeid( double ) );
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
bool StringToFloat::divTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		double result = 0;
		bool isOK = fillInt( string, &result, typeid( double ) );
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
bool StringToFloat::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillInt( string, &result, typeid( double ) );
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
bool StringToFloat::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	
	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillInt( string, &result, typeid( double ) );
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
bool StringToFloat::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	
	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillInt( string, &result, typeid( double ) );
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
bool StringToFloat::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	
	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillInt( string, &result, typeid( double ) );
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
bool StringToFloat::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	
	auto leftVar = isType< double >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		double result = 0;
		bool isOK = fillInt( string, &result, typeid( double ) );
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
