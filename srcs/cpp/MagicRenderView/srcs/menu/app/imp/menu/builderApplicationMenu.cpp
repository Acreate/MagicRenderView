#include "builderApplicationMenu.h"

#include "../../../../app/application.h"
#include "../../../../director/builderDirector.h"
#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/builder/builderPorjectAction.h"
#include "../action/builder/nextStepBuilderAction.h"
#include "../action/builder/runBuilderAction.h"
#include "../action/builder/stopBuilderAction.h"
BuilderApplicationMenu::BuilderApplicationMenu( ) {
}
bool BuilderApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false )
		return false;
	normalMenuAction.builderPorjectAction = application_menu_stack->getAction< BuilderPorjectAction >( );
	if( appendAction( normalMenuAction.builderPorjectAction ) == false )
		return false;

	normalMenuAction.runBuilderAction = application_menu_stack->getAction< RunBuilderAction >( );
	if( appendAction( normalMenuAction.runBuilderAction ) == false )
		return false;

	normalMenuAction.nextStepBuilderAction = application_menu_stack->getAction< NextStepBuilderAction >( );
	if( appendAction( normalMenuAction.nextStepBuilderAction ) == false )
		return false;

	normalMenuAction.stopBuilderAction = application_menu_stack->getAction< StopBuilderAction >( );
	if( appendAction( normalMenuAction.stopBuilderAction ) == false )
		return false;
	setInitVarNumber( tr( "编译" ) );
	return Application::getInstancePtr( )->getBuilderDirector( )->addMenu( this );
}
