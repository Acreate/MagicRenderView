﻿#include "./stringAppend.h"
namespace ifunction {
	static std_shared_ptr< ITypeObject > stringAppend( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
StringAppend::StringAppend( ): IFunctionDeclaration( "string stringAppend(string[] strings)", &ifunction::stringAppend ) { }
