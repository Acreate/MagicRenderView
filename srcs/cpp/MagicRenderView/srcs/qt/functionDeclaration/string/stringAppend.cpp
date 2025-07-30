#include "./stringAppend.h"
namespace ifunction {
	static void stringAppend( const IVarStack &var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return;
	}
}
StringAppend::StringAppend( ): IFunctionDeclaration("void stringAppend(string[] strings)", &ifunction::stringAppend ) { }
