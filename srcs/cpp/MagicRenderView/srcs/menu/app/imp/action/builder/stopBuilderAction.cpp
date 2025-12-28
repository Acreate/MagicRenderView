#include "stopBuilderAction.h"
bool StopBuilderAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "终止节点" ) );
	return true;
}
bool StopBuilderAction::run( QWidget *parent ) {
	return false;
}
