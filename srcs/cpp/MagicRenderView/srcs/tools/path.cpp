#include "path.h"

#include <QDir>
QString path::normalPathSeparator( const QString &normal_target_path ) {
	QString result = normal_target_path;
	result.replace( "\\", "/" );
	auto splitePath = result.split( '/' );
	result = splitePath.join( '/' );
	return result;
}

bool path::createFile( const QString &create_file_path_name ) {
	QFileInfo createFilePath( create_file_path_name );
	if( createFilePath.exists( ) ) {
		if( createFilePath.isFile( ) )
			return true;
		QDir removeDir;
		if( removeDir.remove( create_file_path_name ) == false )
			return false;
		QFile createFile( create_file_path_name );
		if( createFile.open( QIODeviceBase::NewOnly ) == false )
			return false;
		return true;
	}
	auto dir = createFilePath.dir( );
	auto absolutePath = dir.absolutePath( );
	if( dir.mkpath( absolutePath ) == false )
		return false;
	QFile createFile( create_file_path_name );
	if( createFile.open( QIODeviceBase::NewOnly ) == false )
		return false;
	return true;
}
bool path::removeFile( const QString &remove_file_path_name ) {
	QFileInfo removeFilePathInfo( remove_file_path_name );
	if( removeFilePathInfo.exists( ) == false )
		return true;
	if( removeFilePathInfo.isDir( ) == true )
		return false;
	QDir removePath;
	if( removePath.remove( remove_file_path_name ) == false )
		return false;
	return true;
}
bool path::createDir( const QString &create_file_path_name ) {
	QFileInfo createDirPathInfo( create_file_path_name );
	if( createDirPathInfo.exists( ) ) {
		if( createDirPathInfo.isDir( ) )
			return true;
		QDir createFilePath;
		if( createFilePath.remove( create_file_path_name ) == false )
			return false;
		if( createFilePath.mkdir( create_file_path_name ) == false )
			return false;
		return true;
	}
	QDir createDirPath( create_file_path_name );
	if( createDirPath.mkpath( create_file_path_name ) == false )
		return false;
	return true;
}
bool path::removeDir( const QString &remove_file_path_name ) {
	QFileInfo removeFilePathInfo( remove_file_path_name );
	if( removeFilePathInfo.exists( ) == false )
		return true;
	if( removeFilePathInfo.isFile( ) == true )
		return false;
	QDir removePath;
	if( removePath.remove( remove_file_path_name ) == false )
		return false;
	return true;
}
bool path::hasFile( const QString &check_file_path_name ) {
	QFileInfo checkFilePathInfo( check_file_path_name );
	if( checkFilePathInfo.exists( ) == false )
		return false;
	if( checkFilePathInfo.isFile( ) == false )
		return false;
	return true;
}
bool path::hasDir( const QString &check_dir_path_name ) {
	QFileInfo checkFilePathInfo( check_dir_path_name );
	if( checkFilePathInfo.exists( ) == false )
		return false;
	if( checkFilePathInfo.isDir( ) == false )
		return false;
	return true;
}
bool path::getPathHasFileInfo( const QString &check_dir_path_name, QFileInfo &result_file_info ) {
	result_file_info.setFile( check_dir_path_name );
	if( result_file_info.exists( ) )
		return true;
	auto dir = result_file_info.dir( );
	do {
		result_file_info.setFile( dir.absolutePath( ) );
		if( result_file_info.exists( ) )
			return true;
		if( result_file_info.isRoot( ) )
			return false;
		dir = result_file_info.dir( );
	} while( true );
	return false;
}
