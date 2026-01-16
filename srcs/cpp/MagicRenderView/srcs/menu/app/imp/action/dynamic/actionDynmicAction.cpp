#include "actionDynmicAction.h"

#include <director/appDirector.h>
#include <win/mainWindow.h>

#include "../../../../../tools/path.h"

bool ActionDynmicAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "-自定义-" ) );
	setEnabled( false );
	return true;
}
bool ActionDynmicAction::run( MainWindow *parent ) {
	if( dynmicActionCall == nullptr || dynmicActionCall( parent ) == false )
		return false;
	return true;
}
void ActionDynmicAction::setDynmicActionCall( const std::function< bool( MainWindow *parent ) > &dynmic_action_call ) {
	dynmicActionCall = dynmic_action_call;
	if( dynmic_action_call == nullptr )
		setEnabled( false );
	else
		setEnabled( true );
}
