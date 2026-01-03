#include "runBuilderAction.h"

#include "../../../../../win/mainWindow.h"
bool RunBuilderAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "运行节点" ) );
	return true;
}
bool RunBuilderAction::run( MainWindow* parent ) {
	if( parent == nullptr )
		return false;
	return parent->runBuilderBuilderNode( );
}
