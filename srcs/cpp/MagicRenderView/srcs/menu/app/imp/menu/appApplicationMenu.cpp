#include "appApplicationMenu.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/app/aboutAooAction.h"
#include "../action/app/quitAppAction.h"
#include "../action/app/resetAppAction.h"
#include "projectApplicationMenu.h"
AppApplicationMenu::AppApplicationMenu( ) {
}
bool AppApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;

	if( appendAction( application_menu_stack->getAction< QuitAppAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< ResetAppAction >( ) ) == false )
		return false;
	setInitVarNumber( tr( "软件" ) );
	return true;
}
