#include "saveAsProjectAction.h"
bool SaveAsProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "项目另存为" );
	setText( title );
	setObjectName( title );
	return true;
}
