#include "openFileDynamicAction.h"

#include <director/appDirector.h>
#include <win/mainWindow.h>

#include "../../../../../tools/pathTools.h"

bool OpenFileDynamicAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "-空路径-" ) );
	setEnabled( false );
	return true;
}
bool OpenFileDynamicAction::run( MainWindow *parent ) {
	QString openFilePath = this->text( );
	if( pathTools::hasFile( openFilePath ) == false )
		return true;
	if( appDirector->loadAppPorject( parent, openFilePath ) == false )
		return false;
	return true;
}
bool OpenFileDynamicAction::setOpenFilePath( const QString &open_file_path ) {
	if( pathTools::hasFile( open_file_path ) )
		setEnabled( true );
	else
		setEnabled( false );
	setInitVarNumber( open_file_path );
	return true;
}
