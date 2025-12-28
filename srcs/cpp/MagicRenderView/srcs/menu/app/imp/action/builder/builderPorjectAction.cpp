#include "builderPorjectAction.h"
bool BuilderPorjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "编译节点" ) );
	return true;
}
bool BuilderPorjectAction::run( QWidget *parent ) {
	return false;
}
