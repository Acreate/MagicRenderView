#include "appApplicationToolBar.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/app/quitAppAction.h"
#include "../action/app/resetAppAction.h"
AppApplicationToolBar::AppApplicationToolBar( ) {
}
bool AppApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {

	if( NormalApplicationToolBar::init( application_menu_stack ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< QuitAppAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< ResetAppAction >( ) ) == false )
		return false;
	QString title = tr( "软件" );
	setObjectName( title );
	setToolTip( title );
	setWindowTitle( title );
	return true;
}
