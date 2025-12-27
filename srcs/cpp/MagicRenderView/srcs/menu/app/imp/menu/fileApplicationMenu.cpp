#include "fileApplicationMenu.h"
FileApplicationMenu::FileApplicationMenu( const QString &title, QWidget *parent ): NormalApplicationMenu( title, parent ) { }
bool FileApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;
	return true;
}
