#include "nullToAnyType.h"

#include "../../../appType/any.h"
bool NullToAnyType::supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
	auto &typeInfo = typeid( Any );
	if( left_type_info != typeInfo )
		return false;
	if( right_type_info == typeid( nullptr ) )
		return true;
	return true;
}
