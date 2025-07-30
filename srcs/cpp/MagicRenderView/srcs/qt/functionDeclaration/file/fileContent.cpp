#include "./fileContent.h"
namespace ifunction {
	static void fileContent( const IVarStack &var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return;
	}
}
FileContent::FileContent( ): IFunctionDeclaration( "void fileContent(string path)", &ifunction::fileContent ) { }
