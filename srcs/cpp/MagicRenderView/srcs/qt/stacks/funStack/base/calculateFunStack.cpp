#include "./calculateFunStack.h"

#include "../../../functionDeclaration/calculate/calculateAdd.h"
#include "../../../functionDeclaration/calculate/calculateDiv.h"
#include "../../../functionDeclaration/calculate/calculateMul.h"
#include "../../../functionDeclaration/calculate/calculateSub.h"
CalculateFunStack::CalculateFunStack( ) {
	name = "四则运算";
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateAdd ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateSub ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateMul ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateDiv ) );
}
