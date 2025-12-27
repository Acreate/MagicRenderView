#include "projectApplicationMenu.h"
ProjectApplicationMenu::ProjectApplicationMenu( const QString &title, QWidget *parent ): NormalApplicationMenu( title, parent ) { }
bool ProjectApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;
	return true;
}
