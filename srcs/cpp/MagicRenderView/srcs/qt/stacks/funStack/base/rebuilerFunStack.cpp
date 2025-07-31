#include "./rebuilerFunStack.h"

#include "../../../functionDeclaration/rebuilder/rebuildToData.h"
#include "../../../functionDeclaration/rebuilder/rebuildToFloat.h"
#include "../../../functionDeclaration/rebuilder/rebuildToInt.h"
#include "../../../functionDeclaration/rebuilder/rebuildToString.h"
RebuilerFunStack::RebuilerFunStack( ) {
	name = "重生成";
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new RebuildToInt ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new RebuildToFloat ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new RebuildToString ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new RebuildToData ) );
}
