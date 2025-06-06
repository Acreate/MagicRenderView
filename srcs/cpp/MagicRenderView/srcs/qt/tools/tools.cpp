﻿#include "tools.h"
#include <cmake_include_to_c_cpp_header_env.h>
#include <qcoreapplication.h>
#include <qguiapplication.h>
#include <QScreen>
#include <QWindow>
#include <stacktrace>
#include <filesystem>

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
	wss << L"================\t" << appName << " !\n" << msg << L"\n" << L"-----------\n";
	stringType *data = wstringVector.data( );
	for( ; start_index < count; ++start_index )
		wss << data[ start_index ] << L'\n';
	wss << data[ start_index ] << L"\n================";
	qDebug( ) << QString::fromStdWString( wss.str( ) ).toStdString( ).c_str( );
}
