#include "reLoadProjectAction.h"
bool ReLoadProjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "重新加载项目" );
	setText( title );
	setObjectName( title );
	return true;
}
