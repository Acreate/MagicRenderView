#include "./stringSplit.h"
namespace ifunction {
	static std_shared_ptr< ITypeObject > stringSplit( const IVarStack &var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
StringSplit::StringSplit( ): IFunctionDeclaration( "string[] stringSplit(string source_string, string split_key_string)", &ifunction::stringSplit ) { }
