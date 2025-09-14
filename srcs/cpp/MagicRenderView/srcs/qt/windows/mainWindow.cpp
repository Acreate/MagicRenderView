#include "mainWindow.h"

#include <qguiapplication.h>
#include <QMenuBar>
#include <QProcess>
#include <QScrollBar>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPushButton>

#include <qt/tools/tools.h>

#include <qt/application/application.h>

#include <qt/widgets/mainWidget.h>



MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {

	mainMenuBar = menuBar( );
	if( mainMenuBar == nullptr )
		mainMenuBar = new QMenuBar( this );

	mainMenu = new QMenu( "应用", this );
	mainMenuBar->addMenu( mainMenu );

	QAction *action;
	action = mainMenu->addAction( "重启" );
	connect( action, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->resetApp( );
	} );
	action = mainMenu->addAction( "退出" );
	connect( action, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->quitApp( );
	} );

	setWindowToIndexScreenCentre( 0 );

	appInstance = Application::getApplicationInstancePtr( );
	keyFirst = "Application/MainWindow";

	QSize size = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "size" ), this->contentsRect( ).size( ) ).toSize( );
	setBaseSize( size );

	Qt::WindowStates windowStates( appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "windowState" ), this->windowState( ).toInt( ) ).toInt( ) );
	setWindowState( windowStates );
	if( windowStates == Qt::WindowNoState || windowStates == Qt::WindowActive )
		makePos = true;
	else
		makePos = false;

	QPoint point = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "pos" ), this->pos( ) ).toPoint( );
	move( point );
	oldPos = buffPos = point;

	mainScrollArea = new QScrollArea( this );
	mainWidget = new MainWidget( mainScrollArea );
	mainScrollArea->setWidget( mainWidget );
	mainScrollArea->setWidgetResizable( true );
	setCentralWidget( mainScrollArea );
}
MainWindow::~MainWindow( ) {
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "size" ), this->contentsRect( ).size( ) );
	Qt::WindowStates windowState = this->windowState( );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "windowState" ), windowState.toInt( ) );

	if( makePos )
		appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "pos" ), buffPos );
	else
		appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "pos" ), oldPos );
	appInstance->syncAppValueIniFile( );
}
void MainWindow::setWindowToIndexScreenCentre( size_t index ) {
	tools::ui::moveDisplayCenter( this, index );
}
void MainWindow::resizeEvent( QResizeEvent *resize_event ) {
	QMainWindow::resizeEvent( resize_event );
}
void MainWindow::changeEvent( QEvent *event ) {
	QMainWindow::changeEvent( event );
	QEvent::Type type = event->type( );
	switch( type ) {
		case QEvent::WindowStateChange :
			Qt::WindowStates state = windowState( );
			auto newStateFlag = state == Qt::WindowNoState || state == Qt::WindowActive;
			if( newStateFlag == false )
				makePos = false;
			else {
				makePos = true;
				oldPos = buffPos = this->pos( );
			}
			break;
	}
}

bool MainWindow::event( QEvent *event ) {
	QEvent::Type type = event->type( );
	QMoveEvent *widgetMove;
	QPoint point = this->pos( );
	bool eventResult;
	switch( type ) {
		case QEvent::Move :
			eventResult = QMainWindow::event( event );
			widgetMove = static_cast< QMoveEvent * >( event );
			if( widgetMove && makePos )
				buffPos = point;
			return eventResult;
	}
	return QMainWindow::event( event );
}
void MainWindow::mouseMoveEvent( QMouseEvent *event ) {
	QMainWindow::mouseMoveEvent( event );
}
void MainWindow::createNewItemWidget( ItemWidget *generate_new_item_widget, const QRect &contents_rect, const QRect &contents_item_widget_united_rect ) {
	QPoint point = contents_rect.bottomRight( );
	mainScrollArea->ensureVisible( point.x( ), point.y( ) );
}
