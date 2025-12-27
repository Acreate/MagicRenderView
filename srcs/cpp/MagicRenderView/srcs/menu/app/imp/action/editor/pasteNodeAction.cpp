#include "pasteNodeAction.h"
bool PasteNodeAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "粘贴节点" );
	setText( title );
	setObjectName( title );
	return true;
}
