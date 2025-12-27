#include "applicationMenuStack.h"

#include <QMenu>
#include <QToolBar>

#include "../../app/application.h"
#include "../../menu/app/action/normalApplicationAction.h"
#include "../../menu/app/normalApplicationMenu.h"
#include "../../menu/app/normalApplicationToolBar.h"
ApplicationMenuStack::ApplicationMenuStack( QObject *parent ) : QObject( parent ) {

}
bool ApplicationMenuStack::initStack( ) {
	application = Application::getInstancePtr( );

	return true;
}
NormalApplicationToolBar * ApplicationMenuStack::getToolBar( const QString &tool_menu_name ) {
	NormalApplicationToolBar *fromTypeCreate = toolBarGeneratorArray.fromTypeCreate( tool_menu_name );
	if( fromTypeCreate == nullptr ) {
		fromTypeCreate = toolBarGeneratorArray.fromAliasTypeCreate( tool_menu_name );
		if( fromTypeCreate == nullptr )
			return nullptr;
	}
	if( fromTypeCreate->init( this ) == false )
		return nullptr;
	return fromTypeCreate;
}
NormalApplicationMenu * ApplicationMenuStack::getMenu( const QString &tool_menu_name ) {
	NormalApplicationMenu *fromTypeCreate = menuGeneratorArray.fromTypeCreate( tool_menu_name );
	if( fromTypeCreate == nullptr ) {
		fromTypeCreate = menuGeneratorArray.fromAliasTypeCreate( tool_menu_name );
		if( fromTypeCreate == nullptr )
			return nullptr;
	}
	if( fromTypeCreate->init( this ) == false )
		return nullptr;
	return fromTypeCreate;
}
NormalApplicationAction * ApplicationMenuStack::getAction( const QString &acton_name ) {
	NormalApplicationAction *fromTypeCreate = actionGeneratorArray.fromTypeCreate( acton_name );
	if( fromTypeCreate == nullptr ) {
		fromTypeCreate = actionGeneratorArray.fromAliasTypeCreate( acton_name );
		if( fromTypeCreate == nullptr )
			return nullptr;
	}
	if( fromTypeCreate->init( this ) == false )
		return nullptr;
	return fromTypeCreate;
}
