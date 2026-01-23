#include "nextStepBuilderAction.h"

#include "../../../../../director/builderDirector.h"
#include "../../../../../win/mainWindow.h"
bool NextStepBuilderAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "下一步节点" ) );
	return true;
}
bool NextStepBuilderAction::run( MainWindow* parent ) {
	return builderDirector->nextStepBuilderNode( );
}
