#include "./fileInfo.h"
namespace ifunction {
	static void fileInfo( const IVarStack &var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return;
	}
}
FileInfo::FileInfo( ): IFunctionDeclaration( "void fileInfo(string path)", &ifunction::fileInfo ) { }
