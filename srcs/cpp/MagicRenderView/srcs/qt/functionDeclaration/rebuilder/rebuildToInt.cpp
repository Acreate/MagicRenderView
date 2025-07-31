#include "./rebuildToInt.h"

namespace ifunction {
	static std_shared_ptr< ITypeObject > rebuildToInt( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
RebuildToInt::RebuildToInt( ) : IFunctionDeclaration( "string rebuildToInt(void* ptr)", &ifunction::rebuildToInt ) {
}
