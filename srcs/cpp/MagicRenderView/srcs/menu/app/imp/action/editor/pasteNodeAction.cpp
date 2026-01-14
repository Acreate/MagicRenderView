#include "pasteNodeAction.h"

#include "../../../../../director/editorDirector.h"
bool PasteNodeAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "粘贴节点" ) );
	return true;
}
bool PasteNodeAction::run( MainWindow *parent ) {
	return editorDirector->pastePointNodeInfo( );
}
