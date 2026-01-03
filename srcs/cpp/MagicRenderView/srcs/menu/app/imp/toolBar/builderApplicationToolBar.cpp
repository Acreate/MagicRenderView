#include "builderApplicationToolBar.h"

#include "../../../../app/application.h"
#include "../../../../director/builderDirector.h"
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
	normalToolBarAction.builderPorjectAction = application_menu_stack->getAction< BuilderPorjectAction >( );
	if( appendAction( normalToolBarAction.builderPorjectAction ) == false )
		return false;
	normalToolBarAction.runBuilderAction = application_menu_stack->getAction< RunBuilderAction >( );
	if( appendAction( normalToolBarAction.runBuilderAction ) == false )
		return false;
	normalToolBarAction.nextStepBuilderAction = application_menu_stack->getAction< NextStepBuilderAction >( );
	if( appendAction( normalToolBarAction.nextStepBuilderAction ) == false )
		return false;
	normalToolBarAction.stopBuilderAction = application_menu_stack->getAction< StopBuilderAction >( );
	if( appendAction( normalToolBarAction.stopBuilderAction ) == false )
		return false;
	setInitVarNumber( tr( "编译工具" ) );
	return Application::getInstancePtr( )->getBuilderDirector( )->addToolBar( this );
}
