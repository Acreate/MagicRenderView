#include "./stringToFloat.h"

#include "../../I_Type.h"
bool StringToFloat::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	
	if( left_type_info->getTypeInfo( ) != typeid( double ) )
		return false;

	if( right_type_info->getTypeInfo( ) != typeid( QString ) )
		return false;
	bool isOk = false;
	qlonglong resultVar = ( ( QString * ) right )->toLongLong( &isOk );
	if( isOk == false )
		return false;
	*( qlonglong * ) left = resultVar;
	return isOk;
}
