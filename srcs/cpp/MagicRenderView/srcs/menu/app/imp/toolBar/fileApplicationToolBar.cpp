#include "fileApplicationToolBar.h"
FileApplicationToolBar::FileApplicationToolBar( const QString &title, QWidget *parent ) : NormalApplicationToolBar( title, parent ) { }
bool FileApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationToolBar::init( application_menu_stack ) == false )
		return false;
	return true;
}
