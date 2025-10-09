#include "isUint64Type.h"

#include "../I_Var.h"
IsUint64Type::IsUint64Type( ) : I_IsType( ) {
	currentTypeInfo = new I_Type(
		typeid( t_current_type ),
		sizeof( t_current_type ),
		[] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		},
		[]( ) {
			return new t_current_type( );
		});
	updateNameVectorInfo( {
			currentTypeInfo->getTypeInfo( ).name( ),
			"unsigned long long",
			"unsigned int64",
			"unsigned int64_t",
			"uint64",
			"uint64_t",
			"size_t"
		} );

}
bool IsUint64Type::createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function ) const {
	
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
