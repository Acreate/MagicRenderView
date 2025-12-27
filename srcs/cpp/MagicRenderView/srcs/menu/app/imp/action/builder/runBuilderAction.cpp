#include "runBuilderAction.h"
bool RunBuilderAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "运行节点" );
	setText( title );
	setObjectName( title );
	return true;
}
