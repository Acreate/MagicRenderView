#include "./rebuildToFloat.h"

namespace ifunction {
	static std_shared_ptr< ITypeObject > rebuildToFloat( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
RebuildToFloat::RebuildToFloat( ): IFunctionDeclaration( "string rebuildToFloat(void* ptr)", &ifunction::rebuildToFloat ) {
}
