#include "application.h"

#include <qboxlayout.h>

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

std_vector< QWidget * > Application::getLayoutWidgets( QBoxLayout *main_widget ) {
	std_vector< QWidget * > result;
	int count = main_widget->count( );
	for( int index = 0; index < count; ++count ) {
		auto layoutItem = main_widget->itemAt( index );
		if( layoutItem->isEmpty( ) )
			continue;
		auto widget = layoutItem->widget( );
		if( widget == nullptr )
			continue;
		result.emplace_back( widget );
	}
	return result;
}
void Application::deleteLayoutWidgets( QBoxLayout *main_widget ) {
	int count = main_widget->count( );
	for( int index = 0; index < count; ++index ) {
		auto layoutItem = main_widget->itemAt( index );
		if( layoutItem == nullptr )
			continue;
		auto widget = layoutItem->widget( );
		if( widget == nullptr )
			continue;
		delete widget;
	}
}
Application * Application::getApplicationInstancePtr( ) {
	return qobject_cast< Application * >( qApp );
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
