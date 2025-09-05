#include "./logicWhile.h"

namespace ifunction {
	static std_shared_ptr< ITypeObject > LogicWhile( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
LogicWhile::LogicWhile( ) : IFunctionDeclaration( "void LogicWhile(bool logic_flag)", &ifunction::LogicWhile ) {
	isControlCode = true;
}
