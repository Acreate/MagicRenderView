#include "builderApplicationToolBar.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/builder/builderPorjectAction.h"
#include "../action/builder/nextStepBuilderAction.h"
#include "../action/builder/runBuilderAction.h"
#include "../action/builder/stopBuilderAction.h"
BuilderApplicationToolBar::BuilderApplicationToolBar( ) {
}
bool BuilderApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationToolBar::init( application_menu_stack ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< BuilderPorjectAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< RunBuilderAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< NextStepBuilderAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< StopBuilderAction >( ) ) == false )
		return false;
	QString title = tr( "编译工具" );
	setObjectName( title );
	setToolTip( title );
	setWindowTitle( title );
	return true;
}
