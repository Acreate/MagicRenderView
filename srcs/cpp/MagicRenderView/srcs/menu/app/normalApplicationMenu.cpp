#include "normalApplicationMenu.h"

void NormalApplicationMenu::transpondTriggAction( NormalApplicationAction *action ) {
	emit trigg_action_signal( this, action );
}
NormalApplicationMenu::NormalApplicationMenu( ) { }
bool NormalApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( application_menu_stack == nullptr )
		return false;
	if( TranspondTriggNormalActionMenu::init( ) == false )
		return false;
	return true;
}
NormalApplicationMenu::~NormalApplicationMenu( ) {
	emit release_signal( this );
	emit destroyed( this );
}
