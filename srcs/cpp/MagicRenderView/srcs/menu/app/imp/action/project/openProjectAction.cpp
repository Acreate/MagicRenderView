#include "openProjectAction.h"
bool OpenProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "打开项目" ) );
	return true;
}
bool OpenProjectAction::run( QWidget *parent ) {
	return false;
}
