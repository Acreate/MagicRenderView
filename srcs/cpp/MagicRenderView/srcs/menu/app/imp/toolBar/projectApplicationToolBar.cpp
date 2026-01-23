#include "projectApplicationToolBar.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../../../../srack/srackInfo.h"
#include "../action/project/clearProjectAction.h"
#include "../action/project/closeProjectAction.h"
#include "../action/project/openProjectAction.h"
#include "../action/project/reLoadProjectAction.h"
#include "../action/project/saveAsProjectAction.h"
#include "../action/project/savePorjectAction.h"
#include "../action/project/updateProjectAction.h"

ProjectApplicationToolBar::ProjectApplicationToolBar( ) { }
bool ProjectApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationToolBar::init( application_menu_stack ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( NormalApplicationToolBar::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< OpenProjectAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( OpenProjectAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< SavePorjectAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( SavePorjectAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< SaveAsProjectAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( SaveAsProjectAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< ReLoadProjectAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( ReLoadProjectAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< UpdateProjectAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( UpdateProjectAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< ClearProjectAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( ClearProjectAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< CloseProjectAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( CloseProjectAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	setInitVarNumber( tr( "项目工具" ) );
	return true;
}
