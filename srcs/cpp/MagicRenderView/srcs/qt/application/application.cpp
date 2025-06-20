#include "application.h"

#include "../node/nodeComponent/INodeComponent.h"
#include "../node/nodeWidget/INodeWidget.h"

#include "../widget/nodeGraph.h"

#include "qt/tools/tools.h"

NodeGraph *Application::mainNodeGraph = nullptr;

Application::Application( int &argc, char **argv, int i ): QApplication( argc, argv, i ) {
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
	if( mainNodeGraph == nullptr )
		return QApplication::notify( object, event );
	INodeComponent *nodeComponent;
	INodeWidget *nodeWidget;
	QEvent::Type eventType = event->type( );
	switch( eventType ) {
		case QEvent::Show :
			nodeWidget = qobject_cast< INodeWidget * >( object );
			if( nodeWidget ) {
				if( mainNodeGraph->getNodeWidgetID( nodeWidget ) == 0 ) {
					nodeWidget->hide( );
					emit nodeWidget->requestNodeWidgetID( nodeWidget );
				}
				return QApplication::notify( object, event );
			}
			break;
	}
	return QApplication::notify( object, event );
}
