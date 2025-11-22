#include "application.h"

#include "nodeDirector.h"
#include "printfInfo.h"
#include <type/varGenerate.h>

Application *Application::instance = nullptr;
Application * Application::getInstancePtr( ) {
	return instance;
}

Application::Application( int &argc, char **const argv, const int i ) : QApplication( argc, argv, i ) {
}
Application::~Application( ) {
	delete nodeDirector;
	delete printfInfo;
	delete varGenerate;
}
bool Application::init( ) {
	Application::instance = this;
	nodeDirector = new NodeDirector;
	printfInfo = new PrintfInfo;
	varGenerate = new VarGenerate;
	return true;
}
