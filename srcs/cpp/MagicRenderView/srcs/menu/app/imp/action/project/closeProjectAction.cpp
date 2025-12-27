#include "closeProjectAction.h"
bool CloseProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "关闭项目" );
	setText( title );
	setObjectName( title );
	return true;
}
