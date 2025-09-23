#include "./floatToString.h"

#include <cstdint>

#include "../../I_Type.h"
bool FloatToString::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	ChackNeedType( QString, double );
	return true;
}
