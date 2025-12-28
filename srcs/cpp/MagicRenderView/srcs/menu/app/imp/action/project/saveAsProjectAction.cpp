#include "saveAsProjectAction.h"

#include "../../../../../director/appDirector.h"
bool SaveAsProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "项目另存为" ) );
	return true;
}
bool SaveAsProjectAction::run( QWidget *parent ) {
	if( appDirector->saveAsAppProject( parent ) == false )
		return false;
	return true;
}
