#include "savePorjectAction.h"
bool SavePorjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "保存项目" ) );
	return true;
}
bool SavePorjectAction::run( QWidget *parent ) {
	return false;
}
