#include "openFileDynamicAction.h"

#include <director/appDirector.h>
#include <win/mainWindow.h>

bool OpenFileDynamicAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "清理项目" ) );
	return true;
}
bool OpenFileDynamicAction::run( MainWindow *parent ) {
	if( appDirector->clearAppProjectInfo( parent ) == false )
		return false;
	return true;
}
bool OpenFileDynamicAction::setOpenFilePath( const QString &open_file_path ) {
	setInitVarNumber( open_file_path );
	return true;
}
