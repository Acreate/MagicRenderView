#include "isColorType.h"

#include "../I_Type.h"
#include "../I_Var.h"
IsColorType::IsColorType( ) : I_IsType( ) {
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
			currentTypeInfo->getTypeInfo( ).name( ), "QColor", "color", "rgba"
		} );
}
bool IsColorType::createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function ) const {

	if( check_type_info != currentTypeInfo->getTypeInfo( ) )
		return false;
	size_t index = 0;
	for( ; index < aliasTypeNameDataCount; ++index )
		if( aliasTypeNameDataPtr[ index ] == create_name )
			break;
	if( index == aliasTypeNameDataCount )
		return false; // 没有明知
	I_Type *colorType = new I_Type(
		typeid( t_current_type ),
		sizeof( t_current_type ),
		[] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		},
		[]( ) {
			return new t_current_type( );
		}
		);
	I_Var *colorTypeVar = new I_Var( colorType, create_name );
	if( create_is_right_call_back_function( colorTypeVar ) == false )
		delete colorTypeVar;
	return true;
}
