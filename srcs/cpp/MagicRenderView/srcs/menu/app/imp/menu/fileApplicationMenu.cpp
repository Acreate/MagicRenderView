#include "fileApplicationMenu.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../../../../srack/srackInfo.h"
#include "../action/app/quitAppAction.h"
#include "../action/app/resetAppAction.h"
#include "appApplicationMenu.h"
#include "projectApplicationMenu.h"
#include "projectHistoryApplicationMenu.h"
void FileApplicationMenu::triggMenuActionSlot( NormalApplicationMenu *normal_application_menu, NormalApplicationAction *action ) {
	NormalApplicationMenu::triggMenuActionSlot( normal_application_menu, action );
	if( historyApplicationMenu->init( applicationMenuStack ) == false ) {
		auto printerDirector = Application::getInstancePtr( )->getPrinterDirector( );
		printerDirector->info( tr( "ProjectHistoryApplicationMenu 初始化异常" ),Create_SrackInfo( ) );
		return;
	}

}
FileApplicationMenu::FileApplicationMenu( ) {
}
bool FileApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;
	if( appendMenu( application_menu_stack->getMenu< ProjectApplicationMenu >( ) ) == false )
		return false;
	historyApplicationMenu = application_menu_stack->getMenu< ProjectHistoryApplicationMenu >( );
	if( appendMenu( historyApplicationMenu ) == false )
		return false;
	if( appendMenu( application_menu_stack->getMenu< AppApplicationMenu >( ) ) == false )
		return false;
	setInitVarNumber( tr( "文件" ) );
	return true;
}
