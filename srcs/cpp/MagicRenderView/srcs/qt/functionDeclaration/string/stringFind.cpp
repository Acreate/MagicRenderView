#include "./stringFind.h"
namespace ifunction {
	static std_shared_ptr< ITypeObject > stringFind( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
StringFind::StringFind( ): IFunctionDeclaration( "int stringFind(string source_string, string target_string)", &ifunction::stringFind ) { }
