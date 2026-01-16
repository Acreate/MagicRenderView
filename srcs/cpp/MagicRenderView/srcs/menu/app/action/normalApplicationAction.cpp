#include "normalApplicationAction.h"

#include "../../../app/application.h"
void NormalApplicationAction::triggered( ) {
	emit trigg_signal( this );
}
NormalApplicationAction::~NormalApplicationAction( ) {
	emit release_signal( this );
	disconnect( this, &QAction::triggered, this, &NormalApplicationAction::triggered );
}
bool NormalApplicationAction::init( ApplicationMenuStack *application_menu_stack_ptr ) {
	disconnect( this );

	application = Application::getInstancePtr( );
	
	nodeDirector = application->getNodeDirector( );
	printerDirector = application->getPrinterDirector( );
	varDirector = application->getVarDirector( );
	builderDirector = application->getBuilderDirector(  );
	appDirector = application->getAppDirector( );
	editorDirector = application->getEditorDirector(  );
	connect( this, &QAction::triggered, this, &NormalApplicationAction::triggered );
	return true;
}
void NormalApplicationAction::setInitVarNumber( const QString &name ) {
	setText( name );
	setObjectName( name );
}
