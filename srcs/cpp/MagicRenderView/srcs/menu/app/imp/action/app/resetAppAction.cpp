#include "resetAppAction.h"

#include <QDir>
#include <QProcess>

#include "../../../../../app/application.h"
bool ResetAppAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "重启程序" ) );
	return true;
}
bool ResetAppAction::run( QWidget *parent ) {
	application->exit( 0 );
	QProcess::startDetached( application->applicationFilePath( ), application->arguments( ), application->applicationDirPath( ) );
	return true;
}
