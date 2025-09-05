#include "./logicFunStack.h"

#include "../../../functionDeclaration/logic/logicIf.h"
#include "../../../functionDeclaration/logic/logicIfElse.h"
#include "../../../functionDeclaration/logic/logicWhile.h"
LogicFunStack::LogicFunStack( ) {
	name = "逻辑判定";
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new LogicIf ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new LogicIfElse ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new LogicWhile ) );
}
