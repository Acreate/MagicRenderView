#include "cutNodeAction.h"

#include "../../../../../director/editorDirector.h"
bool CutNodeAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	setInitVarNumber( tr( "剪切节点" ) );
	return true;
}
bool CutNodeAction::run( MainWindow* parent ) {
	return editorDirector->cutSelectNodeInfo(  );
}
