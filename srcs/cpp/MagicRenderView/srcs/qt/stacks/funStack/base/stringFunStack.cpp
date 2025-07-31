#include "./stringFunStack.h"

#include "../../../functionDeclaration/string/stringAppend.h"
#include "../../../functionDeclaration/string/stringFind.h"
#include "../../../functionDeclaration/string/stringMid.h"
#include "../../../functionDeclaration/string/stringSplit.h"
StringFunStack::StringFunStack( ) {
	name = "字符串";

	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new StringAppend ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new StringFind ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new StringMid ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new StringSplit ) );
}
