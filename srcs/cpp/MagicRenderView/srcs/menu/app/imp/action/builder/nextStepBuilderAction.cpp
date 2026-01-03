#include "nextStepBuilderAction.h"

#include "../../../../../win/mainWindow.h"
bool NextStepBuilderAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "下一步节点" ) );
	return true;
}
bool NextStepBuilderAction::run( MainWindow* parent ) {
	if( parent == nullptr )
		return false;
	return parent->nextStepBuilderNode( );
}
