#include "clearProjectAction.h"
bool ClearProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "清理项目" );
	setText( title );
	setObjectName( title );
	return true;
}
