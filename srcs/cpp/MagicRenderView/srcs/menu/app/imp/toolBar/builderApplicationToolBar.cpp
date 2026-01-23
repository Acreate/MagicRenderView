#include "builderApplicationToolBar.h"

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
BuilderApplicationToolBar::BuilderApplicationToolBar( ) {
}
bool BuilderApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationToolBar::init( application_menu_stack ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( NormalApplicationToolBar::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	normalToolBarAction.builderPorjectAction = application_menu_stack->getAction< BuilderPorjectAction >( );
	if( appendAction( normalToolBarAction.builderPorjectAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( BuilderPorjectAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	normalToolBarAction.resetBuilderStartNode = application_menu_stack->getAction< ResetBuilderStartNodeProjectAction >( );
	if( appendAction( normalToolBarAction.resetBuilderStartNode ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( ResetBuilderStartNodeProjectAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}
	normalToolBarAction.runBuilderAction = application_menu_stack->getAction< RunBuilderAction >( );
	if( appendAction( normalToolBarAction.runBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( RunBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}
	normalToolBarAction.nextStepBuilderAction = application_menu_stack->getAction< NextStepBuilderAction >( );
	if( appendAction( normalToolBarAction.nextStepBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( NextStepBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}
	normalToolBarAction.stopBuilderAction = application_menu_stack->getAction< StopBuilderAction >( );
	if( appendAction( normalToolBarAction.stopBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( StopBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}
	normalToolBarAction.runToNextFrmeBuilderAction = application_menu_stack->getAction< RunToNextFrmeBuilderAction >( );
	if( appendAction( normalToolBarAction.runToNextFrmeBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( RunToNextFrmeBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	normalToolBarAction.runToTargetNodeBuilderAction = application_menu_stack->getAction< RunToTargetNodeBuilderAction >( );
	if( appendAction( normalToolBarAction.runToTargetNodeBuilderAction ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( RunToTargetNodeBuilderAction::staticMetaObject.className( ) ),Create_SrackInfo( ) );
		return false;
	}

	setInitVarNumber( tr( "编译工具" ) );
	return Application::getInstancePtr( )->getBuilderDirector( )->addToolBar( this );
}
