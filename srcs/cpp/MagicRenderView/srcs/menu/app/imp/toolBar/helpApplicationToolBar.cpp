#include "helpApplicationToolBar.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../../../../srack/srackInfo.h"
#include "../action/app/aboutAooAction.h"
#include "../action/app/quitAppAction.h"
#include "../action/app/resetAppAction.h"
HelpApplicationToolBar::HelpApplicationToolBar( ) {
}
bool HelpApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationToolBar::init( application_menu_stack ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( NormalApplicationToolBar::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< AboutAooAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( AboutAooAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	setInitVarNumber( tr( "帮助工具" ) );
	return true;
}
