#include "savePorjectAction.h"
bool SavePorjectAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	QString title = tr( "保存项目" );
	setText( title );
	setObjectName( title );
	return true;
}
