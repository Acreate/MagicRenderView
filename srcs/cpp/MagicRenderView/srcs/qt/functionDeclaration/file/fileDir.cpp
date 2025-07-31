#include "./fileDir.h"
namespace ifunction {
	static std_shared_ptr< ITypeObject > fileDir( const IVarStack &var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
FileDir::FileDir( ): IFunctionDeclaration( "path fileDir(string path)", &ifunction::fileDir ) { }
