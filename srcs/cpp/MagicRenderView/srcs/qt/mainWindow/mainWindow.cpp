#include "mainWindow.h"

#include <qguiapplication.h>
#include <QMenuBar>
#include <QFileDialog>

#include "qt/tools/tools.h"

#include <qt/widget/scrollArea/scrollNodeGraph.h>
MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ): QMainWindow( parent, flags ) {
	nodeGraph = new ScrollNodeGraph( this );
	nodeGraph->setMainWindow( this );
	setCentralWidget( nodeGraph );
	setWindowToIndexScreenCentre( 0 );
	mainMenuBar = menuBar( );
	if( mainMenuBar == nullptr )
		mainMenuBar = new QMenuBar( this );
	setMenuBar( mainMenuBar );
	QMenu *firstMenu = new QMenu( this );
	firstMenu->setTitle( "首要" );
	mainMenuBar->addMenu( firstMenu );
	auto openFileAction = firstMenu->addAction( "打开文件..." );

	connect( openFileAction, &QAction::triggered, [this]( ) {
		QString openFileName = QFileDialog::getOpenFileName( this, "打开文件", qApp->applicationDirPath( ), "艺术文件(*.mser)" );
		if( openFileName.isEmpty( ) )
			return;
		QFile file( openFileName );
		if( file.open( QIODeviceBase::ReadOnly ) ) {
			QByteArray byteArray = file.readAll( );
			if( nodeGraph->serializeToObjectData( ( const uchar * ) byteArray.data( ), byteArray.size( ) ) == 0 ) {
				tools::debug::printError( "文件无法读取，或者内容失败 : " + file.fileName( ) );
			}
			file.close( );
		}
	} );
	auto saveFileAction = firstMenu->addAction( "存储文件..." );

	connect( saveFileAction, &QAction::triggered, [this]( ) {
		QString openFileName = QFileDialog::getSaveFileName( this, "存储文件", qApp->applicationDirPath( ), "艺术文件(*.mser)" );
		if( openFileName.isEmpty( ) )
			return;
		QFile file( openFileName );
		if( file.open( QIODeviceBase::WriteOnly ) ) {
			std_vector< uchar > ser;
			if( nodeGraph->serializeToVectorData( &ser ) )
				file.write( ( const char * ) ser.data( ), ser.size( ) );
			file.close( );
		}
	} );
	firstMenu->addSeparator( );
	auto exitAction = firstMenu->addAction( "退出" );
	connect( exitAction, &QAction::triggered, []( ) {
		qApp->quit( );
	} );
}
void MainWindow::setWindowToIndexScreenCentre( size_t index ) {
	tools::ui::moveDisplayCenter( this, index );
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
}
