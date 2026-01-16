#include "projectHistoryApplicationMenu.h"

#include "../../../../app/application.h"
#include "../../../../director/appDirector.h"
#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/dynamic/actionDynmicAction.h"
#include "../action/dynamic/openFileDynamicAction.h"

ProjectHistoryApplicationMenu::ProjectHistoryApplicationMenu( ) {

}
bool ProjectHistoryApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	Application *instancePtr;
	AppDirector *appDirector;
	OpenFileDynamicAction *openFileDynamicAction;
	ActionDynmicAction *clearHistortAction;
	std::vector< QString > projectHistort;
	size_t count;
	QString *projectHistoryArray;
	size_t index;
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;

	instancePtr = Application::getInstancePtr( );
	if( instancePtr == nullptr )
		return false;

	appDirector = instancePtr->getAppDirector( );
	if( appDirector == nullptr )
		return false;
	projectHistort = appDirector->getProjectHistory( );
	count = projectHistort.size( );
	if( count ) {
		projectHistoryArray = projectHistort.data( );
		for( index = 0; index < count; ++index ) {
			openFileDynamicAction = application_menu_stack->getAction< OpenFileDynamicAction >( );
			if( appendAction( openFileDynamicAction ) == false )
				return false;
			openFileDynamicAction->setOpenFilePath( projectHistoryArray[ index ] );
		}
	} else {
		openFileDynamicAction = application_menu_stack->getAction< OpenFileDynamicAction >( );
		if( appendAction( openFileDynamicAction ) == false )
			return false;
	}
	addSeparator( );

	clearHistortAction = application_menu_stack->getAction< ActionDynmicAction >( );
	if( appendAction( clearHistortAction ) == false )
		return false;
	clearHistortAction->setInitVarNumber( tr( "清理历史项目" ) );
	clearHistortAction->setDynmicActionCall( [appDirector] ( MainWindow *parent ) {
		return appDirector->clearHirstort( );
	} );
	setInitVarNumber( tr( "历史项目" ) );
	return true;
}
