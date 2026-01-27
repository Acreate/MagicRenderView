#include "menuDirector.h"

#include <QFileDialog>
#include <QShortcut>
#include <win/mainWindow.h>

#include "../app/application.h"
#include "../menuStack/app/applicationMenuStack.h"
#include "../menuStack/edit/editorNodeMenuStack.h"
#include "../menuStack/generateNode/generateNodeMenuStack.h"
#include "../srack/srackInfo.h"
#include "nodeDirector.h"
#include "printerDirector.h"
MenuDirector::MenuDirector( QObject *parent ) : QObject( parent ) {
	instancePtr = nullptr;
	nodeDirector = nullptr;
	printerDirector = nullptr;
	mainWindow = nullptr;
	mainWidget = nullptr;

	generateNodeMenuStack = new GenerateNodeMenuStack;
	applicationMenuStack = new ApplicationMenuStack;
	editorNodeMenuStack = new EditorNodeMenuStack;

}

MenuDirector::~MenuDirector( ) {
	emit release_signal( this, Create_SrackInfo( ) );
	delete generateNodeMenuStack;
	delete applicationMenuStack;
	delete editorNodeMenuStack;
}
bool MenuDirector::init( ) {
	if( generateNodeMenuStack->initStack( ) == false )
		return false;
	if( applicationMenuStack->initStack( ) == false )
		return false;
	if( editorNodeMenuStack->initStack( ) == false )
		return false;
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
	nodeDirector = instancePtr->getNodeDirector( );
	mainWindow = instancePtr->getMainWindow( );
	mainWidget = mainWindow->getMainWidget( );
	return true;
}
