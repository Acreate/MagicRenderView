#include "projectApplicationToolBar.h"

#include "../../../../menuStack/app/applicationMenuStack.h"
#include "../action/project/clearProjectAction.h"
#include "../action/project/closeProjectAction.h"
#include "../action/project/openProjectAction.h"
#include "../action/project/reLoadProjectAction.h"
#include "../action/project/saveAsProjectAction.h"
#include "../action/project/savePorjectAction.h"
#include "../action/project/updateProjectAction.h"

ProjectApplicationToolBar::ProjectApplicationToolBar( ) { }
bool ProjectApplicationToolBar::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationToolBar::init( application_menu_stack ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< OpenProjectAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< SavePorjectAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< SaveAsProjectAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< ReLoadProjectAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< UpdateProjectAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< ClearProjectAction >( ) ) == false )
		return false;
	if( appendAction( application_menu_stack->getAction< CloseProjectAction >( ) ) == false )
		return false;
	setInitVarNumber(tr( "项目工具" ));
	return true;
}
