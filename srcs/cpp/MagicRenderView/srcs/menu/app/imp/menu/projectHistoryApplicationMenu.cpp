#include "projectHistoryApplicationMenu.h"

#include "../../../../app/application.h"
#include "../../../../director/appDirector.h"
#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/dynamic/openFileDynamicAction.h"
ProjectHistoryApplicationMenu::ProjectHistoryApplicationMenu( ) {
}
bool ProjectHistoryApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;

	OpenFileDynamicAction *openFileDynamicAction;

	Application *instancePtr;
	AppDirector *appDirector;
	std::vector< QString > projectHistort;
	size_t count;
	QString *projectHistoryArray;
	size_t index;
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
	}
	setInitVarNumber( tr( "历史项目" ) );
	return true;
}
