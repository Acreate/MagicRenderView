#include "path.h"

#include <QDir>

#include "../app/application.h"

path::pathTree::~pathTree( ) {
	size_t count = subPath.size( );
	if( count == 0 )
		return;
	auto arrayPtr = subPath.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete arrayPtr[ index ];
}
path::pathTree::pathTree( const QString &root_file_name ) {
	auto pathSeparator = path::normalPathSeparatorSplitPath( root_file_name );
	qsizetype count = pathSeparator.size( );
	if( count == 0 )
		return;

	QString *pointer = pathSeparator.data( );
	name = pointer[ 0 ];
	if( count == 1 )
		return;
	// 生成子目录
	qsizetype index = 1;
	pathTree *controlPathTreePtr = this;
	for( ; index < count; ++index ) {
		auto subTree = new pathTree( pointer[ index ] );
		controlPathTreePtr->subPath.emplace_back( subTree );
		controlPathTreePtr = subTree;
	}
}
bool path::pathTree::appSubPath( const QString &sub_file_path ) {
	auto normalPathSeparator = path::normalPathSeparatorToPath( sub_file_path );
	QStringList fileNameList = normalPathSeparator.split( "/" );
	qsizetype count = fileNameList.size( );
	if( count == 0 )
		return false;
	QString *stringArrayPtr = fileNameList.data( );
	auto firstName = stringArrayPtr[ 0 ];
	if( firstName != name )
		return false;
	qsizetype index = 1, subPthArrayIndex;
	count -= 1;
	pathTree *checkPtr = this;
	pathTree **subPathArrayPtr;
	size_t subPthArrayCount;
	QString currentName;
	for( ; index < count; ++index ) {
		currentName = stringArrayPtr[ index ];
		subPathArrayPtr = checkPtr->subPath.data( );
		subPthArrayCount = checkPtr->subPath.size( );
		for( subPthArrayIndex = 0; subPthArrayIndex < subPthArrayCount; ++subPthArrayIndex )
			if( subPathArrayPtr[ subPthArrayIndex ]->name == currentName ) {
				checkPtr = subPathArrayPtr[ subPthArrayIndex ];
				break;
			}
		if( subPthArrayIndex == subPthArrayCount )
			return false;
	}
	currentName = stringArrayPtr[ index ];
	subPathArrayPtr = checkPtr->subPath.data( );
	subPthArrayCount = checkPtr->subPath.size( );
	for( subPthArrayIndex = 0; subPthArrayIndex < subPthArrayCount; ++subPthArrayIndex )
		if( subPathArrayPtr[ subPthArrayIndex ]->name == currentName )
			return true; // 已经存在
	pathTree *subTree = new pathTree( currentName );
	checkPtr->subPath.emplace_back( subTree );
	return true;
}
QString path::normalPathSeparatorToPath( const QString &normal_target_path ) {
	QString result;
	QStringList splitePath = normalPathSeparatorSplitPath( normal_target_path ), buff;
	qsizetype count = splitePath.size( ), index = 0;
	if( count == 0 )
		return result;
	auto pointer = splitePath.data( );
	result = normal_target_path.data( )[ 0 ];
	if( count == 1 )
		return result;
	if( result != '/' )
		result += '/';
	count -= 1;
	do {
		++index;
		if( index == count ) {
			result += pointer[ index ];
			break;
		}
		result += pointer[ index ] + "/";
	} while( true );
	return result;
}
QStringList path::normalPathSeparatorSplitPath( const QString &normal_target_path ) {
	QString buffString = normal_target_path;
	buffString.replace( "\\", "/" );
	QStringList splitePath = buffString.split( '/' ), buff;
	auto count = splitePath.size( );
	if( count == 0 )
		return splitePath;
	auto sourcePtr = splitePath.data( );
	buff.resize( count + 1 ); // 允许超出 1个存储第一个 / 路径名称
	qsizetype index = 0, buffIndex = 0;
	auto targetPrt = buff.data( );
	if( buffString.data( )[ 0 ] == '/' ) {
		targetPrt[ buffIndex ] = "/";
		buffIndex++;
	}
	for( ; index < count; ++index ) {
		if( sourcePtr[ index ].isEmpty( ) )
			continue;
		targetPrt[ buffIndex ] = sourcePtr[ index ];
		++buffIndex;
	}
	buff.resize( buffIndex );
	return buff;
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
