#include "helpApplicationToolBar.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/app/aboutAooAction.h"
#include "../action/app/quitAppAction.h"
#include "../action/app/resetAppAction.h"
HelpApplicationToolBar::HelpApplicationToolBar( ) {
}
bool HelpApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationToolBar::init( application_menu_stack ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< AboutAooAction >( ) ) == false )
		return false;
	setInitVarNumber( tr( "帮助工具" ) );
	return true;
}
