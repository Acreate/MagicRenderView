#include "normalApplicationAction.h"
NormalApplicationAction::~NormalApplicationAction( ) {
	emit release_signal( this );
	emit destroyed( this );
	disconnect( this );
}
bool NormalApplicationAction::init( ApplicationMenuStack* application_menu_stack_ptr ) {
	disconnect( this );
	connect( this, &QAction::triggered, [this]( ) {
		emit trigg_signal( this );
	} );
	return true;
}
bool NormalApplicationAction::run( QWidget *parent ) const {
	if( actionFunction == nullptr )
		return false;
	if( actionFunction( parent ) == false )
		return false;
	return true;
}
