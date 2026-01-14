#include "aboutApplicationWindow.h"

#include <QLabel>
#include <QScrollBar>
#include <QVBoxLayout>

#include "../app/application.h"
#include "../widget/aboutApplicationScrollArea.h"
#include "../widget/aboutApplicationWidget.h"
#include "../widget/mainWidgetScrollArea.h"
#include "mainWindow.h"

AboutApplicationWindow::AboutApplicationWindow( MainWindow *parent_main_wiindow_ptr, Qt::WindowFlags flags ) : QMainWindow( parent_main_wiindow_ptr, flags ),
	parentMainWiindowPtr( parent_main_wiindow_ptr ) {
	hide( );
	aboutApplicationScrollAreaPtr = new AboutApplicationScrollArea( this );
	setCentralWidget( aboutApplicationScrollAreaPtr );
	parent_main_wiindow_ptr->installEventFilter( this );
}
void AboutApplicationWindow::updateWindowGeometry( ) {
	int titleBarHeight = this->frameGeometry( ).height( ) - this->contentsRect( ).height( );
	QPoint point( 0, 0 );
	MainWidgetScrollArea *mainWidgetScrollArea = parentMainWiindowPtr->getMainWidgetScrollArea( );
	point = mainWidgetScrollArea->mapToGlobal( point );
	auto width = mainWidgetScrollArea->width( ) / 3;
	int height = mainWidgetScrollArea->height( ) - mainWidgetScrollArea->horizontalScrollBar( )->height( ) - titleBarHeight;
	point.setX( point.x( ) + width );
	this->setFixedSize( width, height );
	this->move( point );
}
void AboutApplicationWindow::showEvent( QShowEvent *event ) {
	QMainWindow::showEvent( event );
	updateWindowGeometry( );
}
bool AboutApplicationWindow::eventFilter( QObject *watched, QEvent *event ) {
	bool eventFilter = QMainWindow::eventFilter( watched, event );
	if( isHidden( ) )
		return eventFilter;
	auto type = event->type( );
	switch( type ) {
		case QEvent::Resize :
		case QEvent::Move :
			updateWindowGeometry( );
			break;
	}
	return eventFilter;
}
