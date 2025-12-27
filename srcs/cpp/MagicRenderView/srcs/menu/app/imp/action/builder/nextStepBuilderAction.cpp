#include "nextStepBuilderAction.h"
bool NextStepBuilderAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "下一步节点" );
	setText( title );
	setObjectName( title );
	return true;
}
