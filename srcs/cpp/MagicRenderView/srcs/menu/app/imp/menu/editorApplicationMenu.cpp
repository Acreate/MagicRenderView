#include "editorApplicationMenu.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../../../../srack/srackInfo.h"
#include "../action/editor/copyNodeAction.h"
#include "../action/editor/cutNodeAction.h"
#include "../action/editor/pasteNodeAction.h"
EditorApplicationMenu::EditorApplicationMenu( ) {
}
bool EditorApplicationMenu::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationMenu::init( application_menu_stack ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( NormalApplicationMenu::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< CopyNodeAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( CopyNodeAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< CutNodeAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( CutNodeAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	if( appendAction( application_menu_stack->getAction< PasteNodeAction >( ) ) == false ) {
		Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "初始化失败[%1]" ).arg( PasteNodeAction::staticMetaObject.className( ) ), Create_SrackInfo( ) );
		return false;
	}
	setInitVarNumber( tr( "编辑" ) );
	return true;
}
