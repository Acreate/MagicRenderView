#include "reLoadProjectAction.h"

#include "../../../../../director/appDirector.h"
bool ReLoadProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "重新加载项目" ) );
	return true;
}
bool ReLoadProjectAction::run( QWidget *parent ) {
	if( appDirector->reloadAppProject( parent ) == false )
		return false;
	return true;
}
