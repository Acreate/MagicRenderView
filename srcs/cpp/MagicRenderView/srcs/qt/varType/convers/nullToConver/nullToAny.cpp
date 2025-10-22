#include "nullToAny.h"
bool NullToAny::equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
	auto &typeInfo = typeid( nullptr );
	if( left_type_info == typeInfo ) {
		if( right == nullptr || right_type_info == typeInfo )
			*result_bool = true;
		else
			*result_bool = false;
		return true;
	}
	if( right_type_info == typeInfo ) {
		if( left == nullptr )
			*result_bool = true;
		else
			*result_bool = false;
		return true;
	}
	return false;
}
