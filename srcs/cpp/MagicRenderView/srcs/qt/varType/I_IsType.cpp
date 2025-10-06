#include "I_IsType.h"

#include "../application/application.h"
I_IsType::I_IsType( const type_info &current_type_info ) : currentTypeInfo( current_type_info ) {
	varGenerate = Application::getApplicationInstancePtr( )->getVarGenerate( );
}
