#include "application.h"

#include "../node/nodeComponent/INodeComponent.h"
#include "../node/nodeWidget/INodeWidget.h"

#include "../widget/nodeGraph.h"

#include "qt/tools/tools.h"

NodeGraph *Application::mainNodeGraph = nullptr;

Application::Application( int &argc, char **argv, int i ): QApplication( argc, argv, i ) {
}
size_t Application::getID( const INodeComponent *node_component ) {
	if( mainNodeGraph == nullptr )
		return 0;
	return mainNodeGraph->getNodeCompoentID( node_component );
}
size_t Application::getID( const INodeWidget *node_widget ) {
	if( mainNodeGraph == nullptr )
		return 0;
	return mainNodeGraph->getNodeWidgetID( node_widget );
}

void Application::setWindowToIndexScreenCentre( size_t index ) {
	QWindowList windowList = qGuiApp->allWindows( );
	for( QWindow *&win : windowList )
		tools::ui::moveDisplayCenter( win, index );
}

bool Application::notify( QObject *object, QEvent *event ) {
	bool notify = QApplication::notify( object, event );
	if( mainNodeGraph == nullptr )
		return notify;
	INodeComponent *nodeComponent;
	INodeWidget *nodeWidget;
	QEvent::Type eventType = event->type( );

	switch( eventType ) {
		case QEvent::Show :
			nodeComponent = qobject_cast< INodeComponent * >( object );
			if( nodeComponent ) {
				if( mainNodeGraph->getNodeCompoentID( nodeComponent ) == 0 ) {
					nodeComponent->hide( );
					emit nodeComponent->requestNodeComponentID( nodeComponent );
				}
				return notify;
			}
			nodeWidget = qobject_cast< INodeWidget * >( object );

			if( nodeWidget ) {
				if( mainNodeGraph->getNodeWidgetID( nodeWidget ) == 0 ) {
					nodeWidget->hide( );
					emit nodeWidget->requestNodeWidgetID( nodeWidget );
				}
				return notify;
			}
			break;
	}
	return notify;
}
