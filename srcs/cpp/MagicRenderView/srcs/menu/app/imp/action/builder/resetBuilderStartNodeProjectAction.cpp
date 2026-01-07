#include "resetBuilderStartNodeProjectAction.h"

#include "../../../../../director/builderDirector.h"
bool ResetBuilderStartNodeProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "重置开始" ) );
	return true;
}
bool ResetBuilderStartNodeProjectAction::run( MainWindow *parent ) {
	return builderDirector->resetStartNodeProject( );
}
