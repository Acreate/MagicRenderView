#include "projectApplicationToolBar.h"
ProjectApplicationToolBar::ProjectApplicationToolBar( const QString &title, QWidget *parent ) : NormalApplicationToolBar( title, parent ) { }
bool ProjectApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationToolBar::init( application_menu_stack ) == false )
		return false;
	return true;
}
