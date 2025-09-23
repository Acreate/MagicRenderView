#include "./stringToFloat.h"

#include "../../I_Type.h"
bool StringToFloat::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	ChackNeedType( double, intVar, QString, stringVar );
	bool isOk = false;
	double resultVar = stringVar->toDouble( &isOk );
	if( isOk == false )
		return false;
	*intVar = resultVar;
	return isOk;
}
