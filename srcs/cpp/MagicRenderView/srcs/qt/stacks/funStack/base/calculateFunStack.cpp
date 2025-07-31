#include "./calculateFunStack.h"

#include "../../../functionDeclaration/calculate/calculateDiv.h"
#include "../../../functionDeclaration/calculate/calculateFloatAdd.h"
#include "../../../functionDeclaration/calculate/calculateFloatSub.h"
#include "../../../functionDeclaration/calculate/calculateIntAdd.h"
#include "../../../functionDeclaration/calculate/calculateIntSub.h"
#include "../../../functionDeclaration/calculate/calculateMul.h"
CalculateFunStack::CalculateFunStack( ) {
	name = "四则运算";
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateIntAdd ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateIntSub ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateFloatAdd ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateFloatSub ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateMul ) );
	functionList.emplace_back( std_shared_ptr< IFunctionDeclaration >( new CalculateDiv ) );
}
