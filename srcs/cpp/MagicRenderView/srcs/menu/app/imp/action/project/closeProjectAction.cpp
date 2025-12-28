#include "closeProjectAction.h"

#include "../../../../../app/application.h"
#include "../../../../../director/appDirector.h"
#include "../../../../../director/nodeDirector.h"
bool CloseProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "关闭项目" ) );
	return true;
}
bool CloseProjectAction::run( QWidget *parent ) {
	if( appDirector->closeAppProject( parent ) == false )
		return false;
	return true;
}
