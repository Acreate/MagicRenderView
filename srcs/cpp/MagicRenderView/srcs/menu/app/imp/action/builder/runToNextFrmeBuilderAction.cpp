#include "runToNextFrmeBuilderAction.h"

#include "../../../../../director/builderDirector.h"
#include "../../../../../win/mainWindow.h"
bool RunToNextFrmeBuilderAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "运行到下一帧" ) );
	return true;
}
bool RunToNextFrmeBuilderAction::run( MainWindow *parent ) {
	return builderDirector->runToNextFrame( );
}
