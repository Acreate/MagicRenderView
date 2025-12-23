#include "menuDirector.h"

#include "../srack/srackInfo.h"
MenuDirector::~MenuDirector( ) {
	emit release_signal( this, Create_SrackInfo( ) );
}
bool MenuDirector::init( ) {
	return true;
}
