#include "builderPorjectAction.h"
bool BuilderPorjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "编译节点" );
	setText( title );
	setObjectName( title );
	return true;
}
