#include "projectHistoryApplicationMenu.h"

#include "../../../../app/application.h"
#include "../../../../director/appDirector.h"
#include "../../../../director/printerDirector.h"
#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../../../../srack/srackInfo.h"
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
	if( NormalApplicationMenu::init( application_menu_stack ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( NormalApplicationMenu::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}

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
			if( appendAction( openFileDynamicAction ) == false ) {
				Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( OpenFileDynamicAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
				return false;
			}
			openFileDynamicAction->setOpenFilePath( projectHistoryArray[ index ] );
		}
	} else {
		openFileDynamicAction = application_menu_stack->getAction< OpenFileDynamicAction >( );
		if( appendAction( openFileDynamicAction ) == false ) {
			Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( OpenFileDynamicAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
			return false;
		}
	}
	addSeparator( );

	clearHistortAction = application_menu_stack->getAction< ActionDynmicAction >( );
	if( appendAction( clearHistortAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( ActionDynmicAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	clearHistortAction->setInitVarNumber( tr( "清理历史项目" ) );
	clearHistortAction->setDynmicActionCall( [appDirector] ( MainWindow *parent ) {
		return appDirector->clearHirstort( );
	} );
	setInitVarNumber( tr( "历史项目" ) );
	return true;
}
