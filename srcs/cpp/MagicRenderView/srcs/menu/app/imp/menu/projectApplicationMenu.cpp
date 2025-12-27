#include "projectApplicationMenu.h"

#include "../../../../menuStack/app/applicationMenuStack.h"

ProjectApplicationMenu::ProjectApplicationMenu( ) { }
bool ProjectApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction( tr( "打开项目" ) ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction( tr( "保存项目" ) ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction( tr( "另保存项目" ) ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction( tr( "关闭项目" ) ) ) == false )
		return false;
	return true;
}
