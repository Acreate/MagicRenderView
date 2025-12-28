#include "normalApplicationAction.h"

#include "../../../app/application.h"
void NormalApplicationAction::triggered( ) {
	emit trigg_signal( this );
}
NormalApplicationAction::~NormalApplicationAction( ) {
	emit release_signal( this );
	disconnect( this, &QAction::triggered, this, &NormalApplicationAction::triggered );
}
bool NormalApplicationAction::init( ApplicationMenuStack *application_menu_stack_ptr ) {
	disconnect( this );

	application = Application::getInstancePtr( );
	
	nodeDirector = application->getNodeDirector( );
	printerDirector = application->getPrinterDirector( );
	varDirector = application->getVarDirector( );
	
	appDirector = application->getAppDirector( );
	connect( this, &QAction::triggered, this, &NormalApplicationAction::triggered );
	return true;
}