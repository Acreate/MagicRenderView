#include "quitAppAction.h"

#include "../../../../../app/application.h"
bool QuitAppAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "退出程序" ) );
	return true;
}
bool QuitAppAction::run( MainWindow* parent ) {
	application->exit( 0 );
	return true;
}
