#include "printerDirector.h"

#include <stacktrace>
#include <QDir>
#include <cmake_to_c_cpp_header_env.h>
#include <qfileinfo.h>

#include <app/application.h>

bool PrinterDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	applicationName = instancePtr->applicationName( );
	if( absPath )
		delete absPath;
	absPath = new QDir( Cmake_Source_Dir );
	sourceDirPathName = absPath->absolutePath( );
	logSaveFilePathName = instancePtr->getLogSaveFilePathName( );
	return true;
}
PrinterDirector::PrinterDirector( ) : absPath( nullptr ) { }
PrinterDirector::~PrinterDirector( ) {
	delete absPath;
}
void PrinterDirector::error( const QString &msg ) const {
	auto stacktraceEntries = getStacktrace( );
	auto arrayPtr = stacktraceEntries.data( );
	size_t stackTraceEntriesCount = stacktraceEntries.size( );
	if( stackTraceEntriesCount > 2 ) {

		stackTraceEntriesCount -= 2;
		QStringList qstringBuff;
		QDateTime dateTime = QDateTime::currentDateTime( );
		qstringBuff.append( QString( "\n\n============== %1 ============== 错误消息(%2)" ).arg( applicationName ).arg( dateTime.toString( "yyyy-MM-dd hh:mm:ss.z" ) ) );
		QString sourceFrom( "\n%1\n\n-------------------" );
		qstringBuff.append( sourceFrom.arg( msg ) );
		qsizetype removeStartLen = applicationName.size( ) + 1;
		sourceFrom = "\t(%4)=>%1 [ %2 : %3 ]";
		qsizetype lastIndexOf;
		size_t outLineCount = 1;
		QFileInfo fileInfo;
		QString sourceFile;
		QString description;
		QString sourceLine;
		QString appendElement;
		for( size_t index = 0; index < stackTraceEntriesCount; ++index ) {
			auto &stacktraceEntry = arrayPtr[ index ];
			auto line = stacktraceEntry.source_line( );
			if( line == 0 )
				continue;
			sourceFile = QString::fromStdString( stacktraceEntry.source_file( ) );
			fileInfo.setFile( sourceFile );
			sourceFile = fileInfo.absoluteFilePath( );
			if( sourceFile.startsWith( sourceDirPathName ) == false )
				continue;
			sourceFile = absPath->relativeFilePath( sourceFile );
			description = QString::fromStdString( stacktraceEntry.description( ) );
			lastIndexOf = description.lastIndexOf( "+0x" );
			description = description.mid( removeStartLen, lastIndexOf - removeStartLen );
			sourceLine = QString::number( line );
			appendElement = sourceFrom.arg( sourceFile ).arg( description ).arg( sourceLine ).arg( outLineCount );
			qstringBuff << appendElement;
			++outLineCount;
		}
		qstringBuff.append( QString( "==============   ==============\n" ) );
		QString logOutString = qstringBuff.join( "\n" );
		qDebug( ) << logOutString.toStdString( ).c_str( );
		QFile file( logSaveFilePathName );
		if( file.open( QIODeviceBase::ReadWrite | QIODeviceBase::Append ) == false )
			return;
		file.write( logOutString.toUtf8( ) );
	}
}
void PrinterDirector::info( const QString &msg ) const {
	auto stacktraceEntries = getStacktrace( );
	auto arrayPtr = stacktraceEntries.data( );
	size_t stackTraceEntriesCount = stacktraceEntries.size( );
	if( stackTraceEntriesCount > 3 ) {
		stackTraceEntriesCount -= 3;
		QStringList qstringBuff;
		QDateTime dateTime = QDateTime::currentDateTime( );
		qstringBuff.append( QString( "\n\n============== %1 ============== 提示消息(%2)" ).arg( applicationName ).arg( dateTime.toString( "yyyy-MM-dd hh:mm:ss.z" ) ) );
		QString sourceFrom( "\n%1\n\n-------------------" );
		qstringBuff.append( sourceFrom.arg( msg ) );
		qsizetype removeStartLen = applicationName.size( ) + 1;
		sourceFrom = "\t=>%1 [ %2 : %3 ]";
		qsizetype lastIndexOf;

		auto &stacktraceEntry = arrayPtr[ stackTraceEntriesCount ];
		auto sourceFile = QString::fromStdString( stacktraceEntry.source_file( ) );

		sourceFile = absPath->relativeFilePath( sourceFile );

		auto description = QString::fromStdString( stacktraceEntry.description( ) );
		lastIndexOf = description.lastIndexOf( "+0x" );
		description = description.mid( removeStartLen, lastIndexOf - removeStartLen );
		auto sourceLine = QString::number( stacktraceEntry.source_line( ) );
		auto appendElement = sourceFrom.arg( sourceFile ).arg( description ).arg( sourceLine );
		qstringBuff << appendElement;

		qstringBuff.append( QString( "==============   ==============\n" ) );
		QString logOutString = qstringBuff.join( "\n" );
		qDebug( ) << logOutString.toStdString( ).c_str( );
		QFile file( logSaveFilePathName );
		if( file.open( QIODeviceBase::ReadWrite | QIODeviceBase::Append ) == false )
			return;
		file.write( logOutString.toUtf8( ) );
	}
}
std::vector< std::stacktrace_entry > PrinterDirector::getStacktrace( ) const {
	std::vector< std::stacktrace_entry > result;
	auto stacktrace = std::stacktrace::current( );
	size_t stacktraceCount = stacktrace.size( );
	QString appName;
	for( size_t index = 0; index < stacktraceCount; ++index ) {
		auto entry = stacktrace.at( index );
		auto description = entry.description( );
		size_t find = description.find( "!invoke_main+0x" );
		if( description.size( ) > find ) {
			stacktraceCount = index;
			index = 0;
			for( ; index < stacktraceCount; ++index )
				result.emplace_back( stacktrace.at( index ) );
			std::ranges::reverse( result );
			break;
		}
	}

	return result;
}
