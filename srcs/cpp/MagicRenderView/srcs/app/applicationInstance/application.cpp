#include "application.h"

#include "../director/nodeDirector.h"

#include "../printfInfo/printfInfo.h"
Application *Application::instance = nullptr;
Application * Application::getInstancePtr( ) {
	return instance;
}
void Application::setInstancePtr( Application *new_instance ) {
	instance = new_instance;
}
Application::Application( int &argc, char **const argv, const int i ) : QApplication( argc, argv, i ) {
	nodeDirector = new NodeDirector;
	printfInfo = new PrintfInfo;
}
Application::~Application( ) {
	delete nodeDirector;
	delete printfInfo;
}
