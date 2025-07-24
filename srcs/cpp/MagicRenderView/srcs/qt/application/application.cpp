#include "application.h"

#include <QProcess>
#include <qboxlayout.h>

#include "qt/tools/tools.h"

#include <QSettings>
#include <qfile.h>
#include <qfileinfo.h>
Application::Application( int &argc, char **argv, int i ): QApplication( argc, argv, i ) {
	QString fileName = QCoreApplication::applicationDirPath( ) + "/" + applicationDisplayName( ) + ".ini";
	settings = new QSettings( fileName, QSettings::IniFormat );
	QFileInfo fileInfo( fileName );
	if( fileInfo.exists( ) == false ) {
		auto key = "settings";
		settings->setValue( key, 0 );
		settings->sync( );
		settings->remove( key );
		if( fileInfo.exists( ) == false )
			qDebug( ) << "无法创建匹配的 ini 文件";
		else
			settings->sync( );
	}
}
Application::~Application( ) {
	settings->sync( );
	delete settings;
}
void Application::setAppIniValue( const QAnyStringView &key, const QVariant &value ) {
	settings->setValue( key, value );
}
QVariant Application::getAppIniValue( const QAnyStringView &key, const QVariant &defaultValue ) const {
	return settings->value( key, defaultValue );
}
QVariant Application::getAppIniValue( const QAnyStringView &key ) const {
	return settings->value( key );
}
void Application::syncAppValueIniFile( ) const {
	settings->sync( );
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

void Application::resetApp( ) {
	quit( );
	QProcess::startDetached( applicationFilePath( ), arguments( ) );
}
void Application::quitApp( ) {
	quit( );
}
bool Application::notify( QObject *object, QEvent *event ) {

	return QApplication::notify( object, event );
}
