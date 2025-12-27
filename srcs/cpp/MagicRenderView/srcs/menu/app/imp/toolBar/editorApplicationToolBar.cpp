#include "editorApplicationToolBar.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/editor/copyNodeAction.h"
#include "../action/editor/cutNodeAction.h"
#include "../action/editor/pasteNodeAction.h"
EditorApplicationToolBar::EditorApplicationToolBar( ) {
}
bool EditorApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	
	if( NormalApplicationToolBar::init( application_menu_stack ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< CopyNodeAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< CutNodeAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< PasteNodeAction >( ) ) == false )
		return false;
	QString title = tr( "编辑" );
	setObjectName( title );
	setToolTip( title );
	setWindowTitle( title );
	return true;
}
