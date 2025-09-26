#include "I_Stack.h"

#include "../application/application.h"
I_Stack::I_Stack( const type_info &generate_type_info ) : generateTypeInfo( generate_type_info ) {
	this->varGenerate = Application::getApplicationInstancePtr( )->getVarGenerate( );
}
bool I_Stack::getPtrTypeInfo( const void *check_var_ptr, const type_info *&result_type ) const {
	size_t count = stackVarPtr.size( );
	if( count == 0 )
		return false;
	auto data = stackVarPtr.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == check_var_ptr ) {
			result_type = &generateTypeInfo;
			return true;
		}
	return false;
}
