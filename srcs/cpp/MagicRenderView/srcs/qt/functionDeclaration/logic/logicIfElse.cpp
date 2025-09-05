#include "./logicIfElse.h"
namespace ifunction {
	static std_shared_ptr< ITypeObject > LogicIfElse( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
LogicIfElse::LogicIfElse( ) : IFunctionDeclaration( "void LogicIfElse(bool logic_flag)", &ifunction::LogicIfElse ) {
	isControlCode = true;
}
