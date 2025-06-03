#include "application.h"
#include "qt/tools/tools.h"
Application::Application( int &argc, char **argv, int i ): QApplication( argc, argv, i ) {

}

void Application::setWindowToIndexScreenCentre( size_t index ) {
	QWindowList windowList = qGuiApp->allWindows( );
	for( QWindow *&win : windowList )
		tools::ui::moveDisplayCenter( win, index );
}

bool Application::notify( QObject *object, QEvent *event ) {
	return QApplication::notify( object, event );
}
