#include "openProjectAction.h"
bool OpenProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "打开项目" );
	setText( title );
	setObjectName( title );
	return true;
}
