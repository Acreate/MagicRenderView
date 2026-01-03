#include "copyNodeAction.h"

#include "../../../../../director/editorDirector.h"
bool CopyNodeAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "拷贝节点" ) );
	return true;
}
bool CopyNodeAction::run( MainWindow* parent ) {
	return editorDirector->copySelectNodeInfo(  );
}
