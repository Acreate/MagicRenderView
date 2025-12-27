#include "applicationMenuStack.h"

#include <QMenu>
#include <QToolBar>

#include "../../app/application.h"
ApplicationMenuStack::ApplicationMenuStack( QObject *parent ) : QObject( parent ) {

}
bool ApplicationMenuStack::initStack( ) {
	application = Application::getInstancePtr( );

	return true;
}
NormalApplicationToolBar * ApplicationMenuStack::getToolBar( const QString &tool_menu_name ) {
	return nullptr;
}
NormalApplicationMenu * ApplicationMenuStack::getMenu( const QString &tool_menu_name ) {
	return nullptr;
}
NormalApplicationAction * ApplicationMenuStack::getAction( const QString &acton_name ) {
	return nullptr;
}
