#include "./stringMid.h"
namespace ifunction {
	static std_shared_ptr< ITypeObject > stringMid( const IVarStack &var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
StringMid::StringMid( ): IFunctionDeclaration( "string stringMid(string source_string, int start, int end)", &ifunction::stringMid ) { }
