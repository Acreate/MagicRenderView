#include "mainWindow.h"

#include <qguiapplication.h>

#include "qt/event/menu/itemAddMenu.h"
#include "qt/event/window/mainWindowInit.h"
#include "qt/tools/tools.h"
MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ): QMainWindow( parent, flags ) {
	auto mainWindowInit = new MainWindowInit( this );
	qApp->sendEvent( this, mainWindowInit );
}
void MainWindow::setWindowToIndexScreenCentre( size_t index ) {
	tools::ui::moveDisplayCenter( this, index );
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
	auto popMenuEvent = new ItemAddMenu( this );
	qApp->sendEvent( this, popMenuEvent );
}
