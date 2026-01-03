#include "builderDirector.h"

#include "../app/application.h"
#include <win/mainWindow.h>
bool BuilderDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	mainWindow = instancePtr->getMainWindow( );
	return true;
}
bool BuilderDirector::builderNodeProject( ) {
	return mainWindow->builderNodeProject( );
}
bool BuilderDirector::nextStepBuilderNode( ) {
	return mainWindow->nextStepBuilderNode( );
}
bool BuilderDirector::runBuilderBuilderNode( ) {
	return mainWindow->runBuilderBuilderNode( );
}
bool BuilderDirector::stopBuilderBuilderNode( ) {
	return mainWindow->stopBuilderBuilderNode( );
}
