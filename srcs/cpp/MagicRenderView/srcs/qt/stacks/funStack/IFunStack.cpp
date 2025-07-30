#include "./IFunStack.h"

#include "../../application/application.h"

#include "base/calculateFunStack.h"
#include "base/fileFunStack.h"
#include "base/stringFunStack.h"

bool IFunStack::init( ) {
	auto applicationInstancePtr = Application::getApplicationInstancePtr( );
	applicationInstancePtr->appendFunctionStack< CalculateFunStack >( );
	applicationInstancePtr->appendFunctionStack< StringFunStack >( );
	applicationInstancePtr->appendFunctionStack< FileFunStack >( );
	return true;
}
