#include "editorDirector.h"

#include "../app/application.h"
#include "../win/mainWindow.h"
bool EditorDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	mainWindow = instancePtr->getMainWindow( );
	return true;
}
bool EditorDirector::copySelectNodeInfo( ) {
	return mainWindow->copySelectNodeInfo( );
}
bool EditorDirector::pastePointNodeInfo( ) {
	return mainWindow->pastePointNodeInfo( );
}
bool EditorDirector::cutSelectNodeInfo( ) {
	return mainWindow->cutSelectNodeInfo( );
}
bool EditorDirector::cancelNodeInfo( ) {
	return mainWindow->cancelNodeInfo( );
}
bool EditorDirector::deleteSelectNodeInfo( ) {
	return mainWindow->deleteSelectNodeInfo( );
}
bool EditorDirector::calculateNodeRenderSize( ) {
	return mainWindow->calculateNodeRenderSize( );
}
