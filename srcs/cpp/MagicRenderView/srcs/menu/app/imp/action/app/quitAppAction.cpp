#include "quitAppAction.h"
bool QuitAppAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "退出程序" );
	setText( title );
	setObjectName( title );
	return true;
}
