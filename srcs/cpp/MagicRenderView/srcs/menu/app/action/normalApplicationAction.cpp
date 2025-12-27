#include "normalApplicationAction.h"
void NormalApplicationAction::triggered( ) {
	emit trigg_signal( this );
}
NormalApplicationAction::~NormalApplicationAction( ) {
	emit release_signal( this );
	disconnect( this, &QAction::triggered, this, &NormalApplicationAction::triggered );
}
bool NormalApplicationAction::init( ApplicationMenuStack *application_menu_stack_ptr ) {
	disconnect( this );
	connect( this, &QAction::triggered, this, &NormalApplicationAction::triggered );
	return true;
}
bool NormalApplicationAction::run( QWidget *parent ) const {
	if( actionFunction == nullptr )
		return false;
	if( actionFunction( parent ) == false )
		return false;
	return true;
}
