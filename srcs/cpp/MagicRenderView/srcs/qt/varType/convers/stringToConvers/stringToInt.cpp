#include "./stringToInt.h"

#include "../../I_Type.h"

bool StringToInt::fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
	auto call = [this,&left_type_info,left] ( auto *string ) {
		bool isOK = fillInt( string, left, left_type_info );
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
bool StringToInt::addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		int64_t buff;

		if( fillInt( string, &buff, typeid( int64_t ) ) ) {
			*leftVar += buff;
			return true;
		}
		uint64_t ubuff;
		if( fillInt( string, &ubuff, typeid( uint64_t ) ) ) {
			*leftVar += ubuff;
			return true;
		}
		return false;
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
bool StringToInt::subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		int64_t buff;

		if( fillInt( string, &buff, typeid( int64_t ) ) ) {
			*leftVar -= buff;
			return true;
		}
		uint64_t ubuff;
		if( fillInt( string, &ubuff, typeid( uint64_t ) ) ) {
			*leftVar -= ubuff;
			return true;
		}
		return false;
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
bool StringToInt::mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		int64_t buff;

		if( fillInt( string, &buff, typeid( int64_t ) ) ) {
			*leftVar *= buff;
			return true;
		}
		uint64_t ubuff;
		if( fillInt( string, &ubuff, typeid( uint64_t ) ) ) {
			*leftVar *= ubuff;
			return true;
		}
		return false;
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
bool StringToInt::divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar] ( auto *string ) {
		int64_t buff;

		if( fillInt( string, &buff, typeid( int64_t ) ) ) {
			if( buff != 0 )
				*leftVar /= buff;
			return true;
		}
		uint64_t ubuff;
		if( fillInt( string, &ubuff, typeid( uint64_t ) ) ) {
			if( ubuff != 0 )
				*leftVar /= ubuff;
			return true;
		}
		return false;
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
bool StringToInt::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		int64_t buff;

		if( fillInt( string, &buff, typeid( int64_t ) ) ) {
			*result_bool = *leftVar == buff;
			return true;
		}
		uint64_t ubuff;
		if( fillInt( string, &ubuff, typeid( uint64_t ) ) ) {
			*result_bool = *leftVar == ubuff;
			return true;
		}
		return false;
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
bool StringToInt::greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		int64_t buff;

		if( fillInt( string, &buff, typeid( int64_t ) ) ) {
			*result_bool = *leftVar >= buff;
			return true;
		}
		uint64_t ubuff;
		if( fillInt( string, &ubuff, typeid( uint64_t ) ) ) {
			*result_bool = *leftVar >= ubuff;
			return true;
		}
		return false;
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
bool StringToInt::greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		int64_t buff;

		if( fillInt( string, &buff, typeid( int64_t ) ) ) {
			*result_bool = *leftVar > buff;
			return true;
		}
		uint64_t ubuff;
		if( fillInt( string, &ubuff, typeid( uint64_t ) ) ) {
			*result_bool = *leftVar > ubuff;
			return true;
		}
		return false;
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
bool StringToInt::lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		int64_t buff;

		if( fillInt( string, &buff, typeid( int64_t ) ) ) {
			*result_bool = *leftVar <= buff;
			return true;
		}
		uint64_t ubuff;
		if( fillInt( string, &ubuff, typeid( uint64_t ) ) ) {
			*result_bool = *leftVar <= ubuff;
			return true;
		}
		return false;
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
bool StringToInt::lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {

	auto leftVar = isType< int64_t >( left_type_info, left );
	if( leftVar == nullptr )
		return false;
	auto call = [this, leftVar, result_bool] ( auto *string ) {
		int64_t buff;

		if( fillInt( string, &buff, typeid( int64_t ) ) ) {
			*result_bool = *leftVar < buff;
			return true;
		}
		uint64_t ubuff;
		if( fillInt( string, &ubuff, typeid( uint64_t ) ) ) {
			*result_bool = *leftVar < ubuff;
			return true;
		}
		return false;
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
