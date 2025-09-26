#include "I_Stack.h"

#include "../application/application.h"
I_Stack::I_Stack( const type_info &generate_type_info ) : generateTypeInfo( generate_type_info ) {
	this->varGenerate = Application::getApplicationInstancePtr( )->getVarGenerate( );
}
