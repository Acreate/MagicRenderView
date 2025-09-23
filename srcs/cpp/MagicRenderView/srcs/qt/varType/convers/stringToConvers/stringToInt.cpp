#include "./stringToInt.h"

#include "../../I_Type.h"

bool StringToInt::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	ChackNeedType( int64_t, intVar, QString, stringVar );
	bool isOk = false;
	qlonglong resultVar = stringVar->toLongLong( &isOk );
	if( isOk == false )
		return false;
	*intVar = resultVar;
	return isOk;
}
