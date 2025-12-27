#include "appApplicationMenu.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/app/quitAppAction.h"
#include "../action/app/resetAppAction.h"
AppApplicationMenu::AppApplicationMenu( ) {
}
bool AppApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< QuitAppAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< ResetAppAction >( ) ) == false )
		return false;
	QString title = tr( "软件" );
	setObjectName( title );
	setTitle( title );
	return true;
}
