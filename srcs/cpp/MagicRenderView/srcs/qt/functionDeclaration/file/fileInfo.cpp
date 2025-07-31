#include "./fileInfo.h"
namespace ifunction {
	static std_shared_ptr< ITypeObject > fileInfo( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
FileInfo::FileInfo( ): IFunctionDeclaration( "fileInfo fileInfo(string path)", &ifunction::fileInfo ) { }
