#include "isFloat64Type.h"

IsFloat64Type::IsFloat64Type( ) :I_IsType( ) {
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
			currentTypeInfo->getTypeInfo( ).name( ), "double", "double_t", "float64", "float64_t", "double64", "double64_t",
		} );
}
bool IsFloat64Type::createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function ) const {
	return I_IsType::createCheckTypeName( check_type_info, create_name, create_is_right_call_back_function );
}
