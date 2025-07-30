#include "./fileDir.h"
namespace ifunction {
	static void fileDir( const IVarStack &var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return;
	}
}
FileDir::FileDir( ): IFunctionDeclaration( "void fileDir(string path)", &ifunction::fileDir ) { }
