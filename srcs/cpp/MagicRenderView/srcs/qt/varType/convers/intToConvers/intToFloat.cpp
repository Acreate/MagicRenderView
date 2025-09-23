#include "./intToFloat.h"

#include <QString>
#include <cstdint>

#include "../../I_Type.h"
bool IntToFloat::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	ChackNeedType( double, int64_t );
	return true;
}
