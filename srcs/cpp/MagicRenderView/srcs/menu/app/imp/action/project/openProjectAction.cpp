#include "openProjectAction.h"

#include "../../../../../director/appDirector.h"
bool OpenProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "打开项目" ) );
	return true;
}
bool OpenProjectAction::run( QWidget *parent ) {
	if( appDirector->loadAppPorject( ) == false )
		return false;
	return true;
}
