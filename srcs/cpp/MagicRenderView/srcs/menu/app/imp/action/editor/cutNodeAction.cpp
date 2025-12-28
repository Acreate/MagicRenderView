#include "cutNodeAction.h"
bool CutNodeAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "剪切节点" ) );
	return true;
}
bool CutNodeAction::run( QWidget *parent ) {
	return false;
}
