#include "./logicIf.h"

namespace ifunction {
	static std_shared_ptr< ITypeObject > LogicIf( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
LogicIf::LogicIf( ) : IFunctionDeclaration( "void LogicIf(bool logic_flag)", &ifunction::LogicIf ) {
	isControlCode = true;
}
