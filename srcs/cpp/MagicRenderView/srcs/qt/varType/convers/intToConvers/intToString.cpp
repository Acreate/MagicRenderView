#include "./intToString.h"

#include <QString>
#include <cstdint>

#include "../../I_Type.h"
bool IntToString::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	ChackNeedType( int64_t, QString );
	return true;
}
