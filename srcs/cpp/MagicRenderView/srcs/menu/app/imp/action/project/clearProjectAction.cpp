#include "clearProjectAction.h"

#include "../../../../../director/appDirector.h"
#include "../../../../../director/nodeDirector.h"
#include "../../../../../director/varDirector.h"
bool ClearProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "清理项目" ) );
	return true;
}
bool ClearProjectAction::run( QWidget *parent ) {
	if( appDirector->clearAppProjectInfo( parent ) == false )
		return false;
	return true;
}
