#include "mainWindow.h"

#include <qguiapplication.h>

#include "qt/tools/tools.h"

#include <qt/widget/scrollArea/scrollNodeGraph.h>
MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ): QMainWindow( parent, flags ) {
	nodeGraph = new ScrollNodeGraph( this );
	setCentralWidget( nodeGraph );
	
	setWindowToIndexScreenCentre( 0 );
}
void MainWindow::setWindowToIndexScreenCentre( size_t index ) {
	tools::ui::moveDisplayCenter( this, index );
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
}
