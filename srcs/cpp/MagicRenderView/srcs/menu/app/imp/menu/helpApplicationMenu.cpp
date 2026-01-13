#include "helpApplicationMenu.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/app/aboutAooAction.h"
#include "../action/app/quitAppAction.h"
HelpApplicationMenu::HelpApplicationMenu( ) {
}
bool HelpApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< AboutAooAction >( ) ) == false )
		return false;
	setInitVarNumber( tr( "帮助" ) );
	return true;
}
