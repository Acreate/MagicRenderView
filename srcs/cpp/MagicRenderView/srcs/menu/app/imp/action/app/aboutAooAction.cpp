#include "aboutAooAction.h"

#include <QMessageBox>
#include <QVBoxLayout>

#include "../../../../../app/application.h"
#include "../../../../../win/mainWindow.h"
bool AboutAooAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "关于程序" ) );
	return true;
}
bool AboutAooAction::run( MainWindow *parent ) {
	//application->aboutQt( );
	//QMessageBox::aboutQt( parent, application->applicationName( ) );
	parent->popAboutApplicationWindow( );
	return true;
}
