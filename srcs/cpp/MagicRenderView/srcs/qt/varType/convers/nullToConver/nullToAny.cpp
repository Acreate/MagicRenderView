#include "nullToAny.h"
bool NullToAny::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {
	auto &typeInfo = typeid( nullptr );
	if( left_type_info->getTypeInfo( ) != typeInfo )
		return false;
	if( right == nullptr || right_type_info->getTypeInfo( ) == typeInfo ) {
		*result_bool = true;
		return true;
	}
	*result_bool = false;
	return true;
}
