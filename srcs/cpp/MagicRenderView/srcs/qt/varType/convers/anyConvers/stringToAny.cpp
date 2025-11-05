#include "stringToAny.h"

#include "../../../appType/any.h"
bool StringToAny::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	auto &typeInfo = typeid( Any );
	if( left_type_info != typeInfo )
		return false;
	if( right_type_info == typeid( QString ) || right_type_info == typeid( std::wstring ) || right_type_info == typeid( std::string ) )
		return true;
	return false;
}
