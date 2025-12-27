#include "builderApplicationToolBar.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
BuilderApplicationToolBar::BuilderApplicationToolBar( ) {
}
bool BuilderApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationToolBar::init( application_menu_stack ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction( tr( "编译" ) ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction( tr( "运行" ) ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction( tr( "下一步" ) ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction( tr( "停止" ) ) ) == false )
		return false;
	return true;
}
