#include "builderApplicationMenu.h"

#include "../../../../app/application.h"
#include "../../../../director/builderDirector.h"
#include "../../../../director/printerDirector.h"
#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/builder/builderPorjectAction.h"
#include "../action/builder/nextStepBuilderAction.h"
#include "../action/builder/resetBuilderStartNodeProjectAction.h"
#include "../action/builder/runBuilderAction.h"
#include "../action/builder/runToNextFrmeBuilderAction.h"
#include "../action/builder/runToTargetNodeBuilderAction.h"
#include "../action/builder/stopBuilderAction.h"
BuilderApplicationMenu::BuilderApplicationMenu( ) {
}
bool BuilderApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( NormalApplicationMenu::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	normalMenuAction.builderPorjectAction = application_menu_stack->getAction< BuilderPorjectAction >( );
	if( appendAction( normalMenuAction.builderPorjectAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( BuilderPorjectAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	normalMenuAction.resetBuilderStartNode = application_menu_stack->getAction< ResetBuilderStartNodeProjectAction >( );
	if( appendAction( normalMenuAction.resetBuilderStartNode ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( ResetBuilderStartNodeProjectAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	normalMenuAction.runBuilderAction = application_menu_stack->getAction< RunBuilderAction >( );
	if( appendAction( normalMenuAction.runBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( RunBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	normalMenuAction.nextStepBuilderAction = application_menu_stack->getAction< NextStepBuilderAction >( );
	if( appendAction( normalMenuAction.nextStepBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( NextStepBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	normalMenuAction.stopBuilderAction = application_menu_stack->getAction< StopBuilderAction >( );
	if( appendAction( normalMenuAction.stopBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( StopBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	normalMenuAction.runToNextFrmeBuilderAction = applicationMenuStack->getAction< RunToNextFrmeBuilderAction >( );
	if( appendAction( normalMenuAction.runToNextFrmeBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( RunToNextFrmeBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	normalMenuAction.runToTargetNodeBuilderAction = applicationMenuStack->getAction< RunToTargetNodeBuilderAction >( );
	if( appendAction( normalMenuAction.runToTargetNodeBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( RunToTargetNodeBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	setInitVarNumber( tr( "编译" ) );
	return Application::getInstancePtr( )->getBuilderDirector( )->addMenu( this );
}
