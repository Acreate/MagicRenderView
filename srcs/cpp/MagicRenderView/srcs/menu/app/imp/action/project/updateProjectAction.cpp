#include "updateProjectAction.h"
bool UpdateProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "刷新项目" ) );
	return true;
}
bool UpdateProjectAction::run( QWidget *parent ) {
	return false;
}
