#include "./fileContent.h"
namespace ifunction {
	static std_shared_ptr< ITypeObject > fileContent( const IVarStack &global_var_stack, IVarStack &local_var_stack, const IFunctionDeclaration &i_function_declaration ) {
		return nullptr;
	}
}
FileContent::FileContent( ): IFunctionDeclaration( "file fileContent(string path)", &ifunction::fileContent ) { }
