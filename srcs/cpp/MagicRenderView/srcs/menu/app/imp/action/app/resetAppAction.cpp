#include "resetAppAction.h"

#include <QDir>
#include <QProcess>

#include "../../../../../app/application.h"
bool ResetAppAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "重启程序" );
	setText( title );
	setObjectName( title );
	actionFunction = [this] ( QWidget *widget ) {
		application->exit( 0 );
		QProcess::startDetached( application->applicationFilePath( ), application->arguments( ), application->applicationDirPath( ) );
		return true;
	};
	return true;
}
