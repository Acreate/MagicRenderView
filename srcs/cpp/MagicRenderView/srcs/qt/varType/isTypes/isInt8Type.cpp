#include "isInt8Type.h"

#include "../I_Var.h"
IsInt8Type::IsInt8Type( ) : I_IsType( ) {
	currentTypeInfo = new I_Type(
		typeid( t_current_type ),
		sizeof( t_current_type ),
		[] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		},
		[] ( void *&p ) {
			p = new t_current_type();
			return true;
		} );
	updateNameVectorInfo( {
			currentTypeInfo->getTypeInfo( ).name( ),
			"signed char",
			"signed int8",
			"signed int8_t",
			"int8",
			"int8_t"
		} );
}
bool IsInt8Type::createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function ) const {
	
	if( check_type_info != currentTypeInfo->getTypeInfo( ) )
		return false;
	size_t index = 0;
	for( ; index < aliasTypeNameDataCount; ++index )
		if( aliasTypeNameDataPtr[ index ] == create_name ) {
			I_Var *varPtr = new I_Var( *currentTypeInfo, create_name );
			if( create_is_right_call_back_function( varPtr ) == false )
				delete varPtr;
			return true;
		}
	return false;
}
