#include "tools.h"
#include <cmake_include_to_c_cpp_header_env.h>
#include <qcoreapplication.h>
#include <qguiapplication.h>
#include <QScreen>
#include <QWindow>
#include <stacktrace>
#include <filesystem>
#include <QByteArray>
#include <qfileinfo.h>

int tools::ui::moveDisplayCenter( QWidget *move_target, size_t display_target ) {
	QList< QScreen * > screens = qGuiApp->screens( );
	qsizetype screenCount = screens.size( );
	if( screenCount < display_target /* 个数小于目标 */ )
		return -1;
	auto screen = screens[ display_target ];
	QRect geometry = screen->geometry( );
	QSize windowSize = move_target->size( );
	auto newX = ( geometry.width( ) - windowSize.width( ) ) / 2 + geometry.x( );
	auto newY = ( geometry.height( ) - windowSize.height( ) ) / 2 + geometry.y( );
	move_target->setGeometry( newX, newY, windowSize.width( ), windowSize.height( ) );
	return 0;
}
int tools::ui::moveDisplayCenter( QWindow *move_target, size_t display_target ) {
	QList< QScreen * > screens = qGuiApp->screens( );
	qsizetype screenCount = screens.size( );
	if( screenCount < display_target /* 个数小于目标 */ )
		return -1;
	auto screen = screens[ display_target ];
	QRect geometry = screen->geometry( );
	QSize windowSize = move_target->size( );
	auto newX = ( geometry.width( ) - windowSize.width( ) ) / 2 + geometry.x( );
	auto newY = ( geometry.height( ) - windowSize.height( ) ) / 2 + geometry.y( );
	move_target->setGeometry( newX, newY, windowSize.width( ), windowSize.height( ) );
	return 0;
}

std_vector< std_pairt< QString, size_t > > & tools::debug::getFunctionName( size_t start, size_t leven, std_vector< std_pairt< QString, size_t > > &result_pairt ) {
	result_pairt.clear( );
	std_vector< std_pairt< QString, size_t > > buff;
	auto applicationName = qApp->applicationName( );
	auto stacktrace = std::stacktrace::current( );
	for( auto &iterator : stacktrace ) {
		QString fromStdString = QString::fromStdString( iterator.description( ) );
		qsizetype indexOf = fromStdString.indexOf( applicationName );
		if( indexOf == -1 )
			continue;
		buff.emplace_back( fromStdString, iterator.source_line( ) );
	}
	size_t count = buff.size( );
	//count = count > leven ? leven : count;
	auto data = buff.data( );
	qsizetype indexOf;
	qint64 position = applicationName.size( ) + 1;
	for( size_t index = start + 1; index < count; ++index ) {
		if( leven == 0 )
			break;
		--leven;
		auto &pair = data[ index ];
		auto &first = pair.first;

		indexOf = first.indexOf( applicationName );
		if( indexOf != -1 ) {
			qsizetype end = first.indexOf( "+0x" );
			first = first.mid( position, end - position );
		}
		result_pairt.emplace_back( pair );
		indexOf = first.indexOf( "!main+0x" );
		if( indexOf != -1 )
			break;
	}

	return result_pairt;
}
void tools::debug::printError( const std::wstring &msg, size_t start_index, size_t last_remove_count ) {
	using stringType = std::wstring;
	using stringStreamType = std::wstringstream;

	/// 项目根路径的绝对路径
	stringType cmakeHomeAbsolutePath = std::filesystem::absolute( cmake_value_CMAKE_HOME_DIRECTORY ).wstring( );
	size_t cmakeHomeCount = cmakeHomeAbsolutePath.size( );
	std::vector< stringType > wstringVector;
	auto stacktrace = std::stacktrace::current( );
	for( auto &iterator : stacktrace ) {
		stringType sourceFileAbsolutePath = std::filesystem::absolute( iterator.source_file( ) ).wstring( );
		if( sourceFileAbsolutePath.starts_with( cmakeHomeAbsolutePath ) ) {
			QString descri = QString::fromStdString( iterator.description( ) );
			qsizetype satrtIndex = descri.indexOf( "!" );
			qsizetype lastIndexOf = descri.lastIndexOf( "+0x" );
			satrtIndex += 1;
			descri = descri.mid( satrtIndex, lastIndexOf - satrtIndex );
			auto description = descri.toStdWString( );
			auto string = sourceFileAbsolutePath.substr( cmakeHomeCount ) + L" ( " + std::to_wstring( iterator.source_line( ) ) + L" )" + L"\n\t=> " + description;
			wstringVector.emplace_back( string );
		}
	}
	size_t count = wstringVector.size( );
	if( count >= last_remove_count )
		count -= last_remove_count;
	stringStreamType wss;
	auto appName = qApp->applicationDisplayName( ).toStdWString( );
	wss << L"\n================\t" << appName << " !\t============\n" << msg << L"\n" << L"---------------------------------\n";
	stringType *data = wstringVector.data( );
	for( ; start_index < count; ++start_index )
		wss << data[ start_index ] << L'\n';
	if( start_index < count )
		wss << data[ start_index ] << L'\n';
	wss << L"================================================\n";
	qDebug( ) << QString::fromStdWString( wss.str( ) ).toStdString( ).c_str( );
}
void tools::debug::printInfo( const QString &info_msg ) {
	auto applicationName = qApp->applicationName( );
	auto stacktrace = std::stacktrace::current( );
	const std::stacktrace_entry &stacktraceEntry = stacktrace.operator[]( 1 );

	QString description = QString::fromStdString( stacktraceEntry.description( ) );
	QString currentCodeSourceFile = QString::fromStdString( stacktraceEntry.source_file( ) );
	QString line = QString::number( stacktraceEntry.source_line( ) );

	// 去除 +0x
	qsizetype lastIndexOf = description.lastIndexOf( "+0x" );
	// 去除 标题 !
	qsizetype startIndexOf = description.lastIndexOf( "!" ) + 1;
	description = description.mid( startIndexOf, lastIndexOf - startIndexOf );
	QFileInfo homePath( cmake_value_CMAKE_HOME_DIRECTORY );
	QFileInfo sourcePath( currentCodeSourceFile );
	currentCodeSourceFile = sourcePath.absoluteFilePath( ).remove( homePath.absoluteFilePath( ) );
	qDebug( ) << "== 消息显示::=> " << applicationName.toStdString( ).c_str( ) << "\n!"
		<< "(" << description.toStdString( ).c_str( ) << ")"
		<< currentCodeSourceFile.toStdString( ).c_str( )
		<< "[" << line.toStdString( ).c_str( ) << "]"
		<< "\n\n"
		<< info_msg.toStdString( ).c_str( ) << "\n\n=========== 消息 end\n";
}

QString tools::qstr::removeSpace( const QString &string ) {
	qsizetype length = string.length( );
	if( length == 0 )
		return string;
	QChar *buff = new QChar[ length ];
	qsizetype buffIndex = 0;
	qsizetype compIndex = 0;
	auto data = string.data( );

	for( ; compIndex < length; ++compIndex )
		if( data[ compIndex ].isSpace( ) == false ) {
			buff[ buffIndex ] = data[ compIndex ];
			++buffIndex;
		}
	QString result( buff, buffIndex );
	delete[] buff;
	return result;
}
