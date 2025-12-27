#include "resetAppAction.h"
bool ResetAppAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "重启程序" );
	setText( title );
	setObjectName( title );
	return true;
}
