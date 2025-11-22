#include "./printfInfo.h"

#include <stacktrace>
#include <QDebug>
#include <QDir>
#include <cmake_to_c_cpp_header_env.h>
#include <qfileinfo.h>

#include "application.h"

void PrintfInfo::error( const QString &msg ) const {
	auto stacktraceEntries = getStacktrace( );
	auto arrayPtr = stacktraceEntries.data( );
	size_t stackTraceEntriesCount = stacktraceEntries.size( );
	if( stackTraceEntriesCount > 2 ) {
		stackTraceEntriesCount -= 2;
		QStringList qstringBuff;
		QString applicationName = Application::getInstancePtr( )->applicationName( );
		qstringBuff.append( QString( "============== %1 ============== 错误消息" ).arg( applicationName ) );
		QString sourceFrom( "%1\n-------------------" );
		qstringBuff.append( sourceFrom.arg( msg ) );
		qsizetype removeStartLen = applicationName.size( ) + 1;
		sourceFrom = "\t=>%1 [ %2 : %3 ]";
		qsizetype lastIndexOf;
		QDir absPath( Cmake_Source_Dir );
		for( size_t index = 0; index < stackTraceEntriesCount; ++index ) {
			auto &stacktraceEntry = arrayPtr[ index ];
			auto sourceFile = QString::fromStdString( stacktraceEntry.source_file( ) );

			sourceFile = absPath.relativeFilePath( sourceFile );

			auto description = QString::fromStdString( stacktraceEntry.description( ) );
			lastIndexOf = description.lastIndexOf( "+0x" );
			description = description.mid( removeStartLen, lastIndexOf - removeStartLen );
			auto sourceLine = QString::number( stacktraceEntry.source_line( ) );
			auto appendElement = sourceFrom.arg( sourceFile ).arg( description ).arg( sourceLine );
			qstringBuff << appendElement;
		}
		qstringBuff.append( QString( "==============   ==============" ) );
		qDebug( ) << qstringBuff.join( "\n" ).toStdString( ).c_str( );
	}
}
void PrintfInfo::info( const QString &msg ) const {
	auto stacktraceEntries = getStacktrace( );
	auto arrayPtr = stacktraceEntries.data( );
	size_t stackTraceEntriesCount = stacktraceEntries.size( );
	if( stackTraceEntriesCount > 3 ) {
		stackTraceEntriesCount -= 3;
		QStringList qstringBuff;
		QString applicationName = Application::getInstancePtr( )->applicationName( );
		qstringBuff.append( QString( "============== %1 ============== 提示消息" ).arg( applicationName ) );
		QString sourceFrom( "%1\n-------------------" );
		qstringBuff.append( sourceFrom.arg( msg ) );
		qsizetype removeStartLen = applicationName.size( ) + 1;
		sourceFrom = "\t=>%1 [ %2 : %3 ]";
		qsizetype lastIndexOf;
		QDir absPath( Cmake_Source_Dir );

		auto &stacktraceEntry = arrayPtr[ stackTraceEntriesCount ];
		auto sourceFile = QString::fromStdString( stacktraceEntry.source_file( ) );

		sourceFile = absPath.relativeFilePath( sourceFile );

		auto description = QString::fromStdString( stacktraceEntry.description( ) );
		lastIndexOf = description.lastIndexOf( "+0x" );
		description = description.mid( removeStartLen, lastIndexOf - removeStartLen );
		auto sourceLine = QString::number( stacktraceEntry.source_line( ) );
		auto appendElement = sourceFrom.arg( sourceFile ).arg( description ).arg( sourceLine );
		qstringBuff << appendElement;

		qstringBuff.append( QString( "==============   ==============" ) );
		qDebug( ) << qstringBuff.join( "\n" ).toStdString( ).c_str( );
	}
}
std::vector< std::stacktrace_entry > PrintfInfo::getStacktrace( ) const {
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
