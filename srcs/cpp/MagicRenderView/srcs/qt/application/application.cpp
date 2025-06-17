#include "application.h"

#include "../node/nodeComponent/INodeComponent.h"
#include "../node/nodeWidget/INodeWidget.h"

#include "qt/tools/tools.h"
Application::Application( int &argc, char **argv, int i ): QApplication( argc, argv, i ) {
}

void Application::setWindowToIndexScreenCentre( size_t index ) {
	QWindowList windowList = qGuiApp->allWindows( );
	for( QWindow *&win : windowList )
		tools::ui::moveDisplayCenter( win, index );
}

bool Application::notify( QObject *object, QEvent *event ) {
	INodeComponent *nodeComponent;
	INodeWidget *nodeWidget;
	bool notify = QApplication::notify( object, event );
	switch( event->type( ) ) {
		case QEvent::Show :
			nodeComponent = qobject_cast< INodeComponent * >( object );
			if( nodeComponent ) {
				if( nodeComponent->getNodeComponentId( ) == 0 ) {
					nodeComponent->hide( );
					emit nodeComponent->requestNodeComponentID( nodeComponent );
				}
				return notify;
			}
			nodeWidget = qobject_cast< INodeWidget * >( object );

			if( nodeWidget ) {
				if( nodeWidget->getNodeWidgetId( ) == 0 ) {
					nodeWidget->hide( );
					emit nodeWidget->requestNodeWidgetID( nodeWidget );
				}
				return notify;
			}
			break;
	}
	return notify;
}
