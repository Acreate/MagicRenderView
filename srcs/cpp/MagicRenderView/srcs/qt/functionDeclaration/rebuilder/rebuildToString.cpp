#include "./rebuildToString.h"

namespace ifunction {
	static std_shared_ptr< ITypeObject > rebuildToString( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
RebuildToString::RebuildToString( ): IFunctionDeclaration( "string rebuildToString(void* ptr)", &ifunction::rebuildToString ) {
}
