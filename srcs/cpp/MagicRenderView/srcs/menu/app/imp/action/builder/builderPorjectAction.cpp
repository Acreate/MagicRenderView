#include "builderPorjectAction.h"

#include "../../../../../director/builderDirector.h"
#include "../../../../../win/mainWindow.h"
bool BuilderPorjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "编译节点" ) );
	return true;
}
bool BuilderPorjectAction::run( MainWindow *parent ) {
	return builderDirector->builderNodeProject( );
}
