#include "fileApplicationMenu.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/app/quitAppAction.h"
#include "../action/app/resetAppAction.h"
#include "appApplicationMenu.h"
#include "projectApplicationMenu.h"
#include "projectHistoryApplicationMenu.h"
FileApplicationMenu::FileApplicationMenu( ) {
}
bool FileApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;
	if( appendMenu( application_menu_stack->getMenu< ProjectApplicationMenu >( ) ) == false )
		return false;
	if( appendMenu( application_menu_stack->getMenu< ProjectHistoryApplicationMenu >( ) ) == false )
		return false;
	if( appendMenu( application_menu_stack->getMenu< AppApplicationMenu >( ) ) == false )
		return false;
	setInitVarNumber( tr( "文件" ) );
	return true;
}
