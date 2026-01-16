#include "normalApplicationToolBar.h"

#include "normalApplicationMenu.h"

void NormalApplicationToolBar::transpondTriggAction( NormalApplicationAction *action ) {
	emit trigg_action_signal( this, action );
}
NormalApplicationToolBar::NormalApplicationToolBar( ) { }
bool NormalApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( application_menu_stack == nullptr )
		return false;
	if( TranspondTriggNormalActionToolsBar::init( ) == false )
		return false;
	return true;
}

NormalApplicationToolBar::~NormalApplicationToolBar( ) {
	emit release_signal( this );
}
