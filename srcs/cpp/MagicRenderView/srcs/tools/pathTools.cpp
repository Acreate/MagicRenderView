#include "pathTools.h"

#include <QDir>
#include <QProcess>

#include <cmake_to_c_cpp_header_env.h>
#include <director/printerDirector.h>
#include <srack/srackInfo.h>

#include "../app/application.h"

pathTools::pathTree::~pathTree( ) {
	size_t count = subPath.size( );
	if( count == 0 )
		return;
	auto arrayPtr = subPath.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete arrayPtr[ index ];
}
pathTools::pathTree::pathTree( const QString &root_file_name ) : parentPathTree( nullptr ) {
	auto pathSeparator = pathTools::normalPathSeparatorSplitPath( root_file_name );
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
void pathTools::pathTree::getAbsolutePath( QString &result_absolute_path ) {
	result_absolute_path.clear( );

	auto contrlPtr = this;
	result_absolute_path = contrlPtr->name;
	contrlPtr = contrlPtr->parentPathTree;
	while( contrlPtr ) {
		result_absolute_path = contrlPtr->name + '/' + result_absolute_path;
		contrlPtr = contrlPtr->parentPathTree;
	}
}
bool pathTools::pathTree::appSubPath( const QString &sub_file_path ) {
	auto normalPathSeparator = pathTools::normalPathSeparatorSplitPath( sub_file_path );
	qsizetype count = normalPathSeparator.size( ), index = 0;
	if( count == 0 )
		return false;
	auto data = normalPathSeparator.data( );
	pathTree *currentPathTreePtr = this;
	size_t subCount;
	pathTree **subData;
	size_t subIndex;
	QString appendName;
	pathTree *newPathTreePtr;
	for( ; index < count; ++index ) {
		appendName = data[ index ];
		subCount = currentPathTreePtr->subPath.size( );
		subData = currentPathTreePtr->subPath.data( );
		for( subIndex = 0; subIndex < subCount; ++subIndex )
			if( subData[ subIndex ]->name == appendName ) {
				currentPathTreePtr = subData[ subIndex ];
				break;
			}
		if( subIndex != subCount )
			continue; // 目录已经存在
		newPathTreePtr = new pathTree( appendName );
		newPathTreePtr->parentPathTree = currentPathTreePtr;
		currentPathTreePtr->subPath.emplace_back( newPathTreePtr );
		currentPathTreePtr = newPathTreePtr;
	}
	return true;
}
QString pathTools::pathTree::toQString( size_t index, QChar fill_char ) const {
	QString tabChar( index, fill_char );
	QString result = tabChar + name;
	size_t currentCount = subPath.size( );
	if( currentCount == 0 )
		return result;
	auto currentData = subPath.data( );
	size_t currentIndex = 0;
	for( ; currentIndex < currentCount; ++currentIndex )
		result = result + '\n' + currentData[ currentIndex ]->toQString( index + 1, fill_char );
	return result;
}

bool pathTools::getFileOwner( const QString &get_file_path, QString &result_file_owner ) {
	// 先检查文件是否存在
	QFileInfo fileInfo( get_file_path );
	if( !fileInfo.exists( ) )
		return false;
	result_file_owner = fileInfo.absoluteFilePath( );
	QProcess process;
	QStringList standarOutputSplit;
	QProcessEnvironment environment = QProcessEnvironment::systemEnvironment( );
#ifdef Q_OS_WIN
	// Windows平台

	auto pathValue = environment.value( "path" );
	pathValue.append( ";" ).append( QDir::currentPath( ) );
	environment.insert( "path", pathValue );
	process.setProcessEnvironment( environment );
	process.setProcessChannelMode( QProcess::MergedChannels );

	standarOutputSplit.append( "/c" );
	standarOutputSplit.append( result_file_owner.mid( 0, 2 ) );
	standarOutputSplit.append( "&&" );
	standarOutputSplit.append( "dir" );
	standarOutputSplit.append( "/q" );
	result_file_owner = fileInfo.absoluteDir( ).absolutePath( );
	result_file_owner = result_file_owner.mid( 3 );
	result_file_owner = QObject::tr( "\"%1\"" ).arg( result_file_owner ).toLocal8Bit( );
	standarOutputSplit.append( result_file_owner );
	process.start( "cmd.exe", standarOutputSplit );

	process.waitForFinished( );

	result_file_owner = process.readAllStandardOutput( ).trimmed( );
	if( result_file_owner.isEmpty( ) )
		return false;
	standarOutputSplit = result_file_owner.split( "\n" );
	qsizetype outCount = standarOutputSplit.size( );
	if( outCount == 0 )
		return false;
	QString *outArray;
	QStringList subSplit;
	qsizetype subCount, index, subIndex;
	QString *data;
	result_file_owner = fileInfo.fileName( );
	outArray = standarOutputSplit.data( );
	for( index = 0; index < outCount; ++index ) {
		subSplit = outArray[ index ].split( " " );
		subCount = subSplit.size( );
		if( subCount == 0 )
			continue;
		data = subSplit.data( );
		for( subIndex = 0; subIndex < subCount; ++subIndex ) {
			data[ subIndex ] = data[ subIndex ].trimmed( );
			if( data[ subIndex ].isEmpty( ) )
				continue;
			if( data[ subIndex ] == result_file_owner ) {
				--subIndex;
				for( ; subIndex != 0; --subIndex )
					if( data[ subIndex ].isEmpty( ) == false ) {
						result_file_owner = data[ subIndex ];
						return true; // 匹配到了
					}
			}
		}
	}
	return false;

#elif defined(Q_OS_LINUX)
	// Linux平台：读取扩展属性（需要安装attr库）
	process.start( "getfattr", QStringList( ) << "-n" << "user.author" << "--only-values" << get_file_path );
	process.waitForFinished( );
	result_file_owner = process.readAllStandardOutput( ).trimmed( );
	if( result_file_owner.isEmpty( ) )
		return false;
	return true;

#elif defined(Q_OS_MACOS)
	// macOS平台：使用mdls命令读取元数据
	process.start( "mdls", QStringList( ) << "-name" << "kMDItemAuthors" << "-raw" << get_file_path );
	process.waitForFinished( );

	QString author = process.readAllStandardOutput( ).trimmed( );
	if( author.isEmpty( ) )
		return false;
	return true;
#else
	return false;
#endif
}
bool pathTools::getNormalBaseName( const QString &normal_target_path, QString &result_bse_nmae ) {
	auto pathSeparatorSplitPath = normalPathSeparatorSplitPath( normal_target_path );
	qsizetype count = pathSeparatorSplitPath.size( );
	if( count == 0 )
		return false;
	result_bse_nmae = pathSeparatorSplitPath.last( );
	return true;
}
QString pathTools::normalPathSeparatorToPath( const QString &normal_target_path ) {
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
		result = pointer[ 0 ] + '/';
	else
		result += pointer[ 0 ] + '/';
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
QStringList pathTools::normalPathSeparatorSplitPath( const QString &normal_target_path ) {
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
QString pathTools::relativeRootFilePath( const QString &file_path ) {
	return QDir( Cmake_Source_Dir ).relativeFilePath( file_path );
}

bool pathTools::createFile( const QString &create_file_path_name ) {
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
bool pathTools::removeFile( const QString &remove_file_path_name ) {
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
bool pathTools::createDir( const QString &create_file_path_name ) {
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
bool pathTools::removeDir( const QString &remove_file_path_name ) {
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
bool pathTools::hasFile( const QString &check_file_path_name ) {
	QFileInfo checkFilePathInfo( check_file_path_name );
	if( checkFilePathInfo.exists( ) == false )
		return false;
	if( checkFilePathInfo.isFile( ) == false )
		return false;
	return true;
}
bool pathTools::hasDir( const QString &check_dir_path_name ) {
	QFileInfo checkFilePathInfo( check_dir_path_name );
	if( checkFilePathInfo.exists( ) == false )
		return false;
	if( checkFilePathInfo.isDir( ) == false )
		return false;
	return true;
}
bool pathTools::getPathHasFileInfo( const QString &check_dir_path_name, QFileInfo &result_file_info ) {
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
bool pathTools::getOnPathInfoVector( const QString &get_path, std::vector< QString > &result_dir_path_vector, std::vector< QString > &result_file_path_vector ) {
	QDir info( get_path );
	if( info.exists( ) == false )
		return false;
	auto entryInfoList = info.entryInfoList( QDir::NoDotAndDotDot );
	qsizetype count = entryInfoList.size( );
	auto entryInfoArray = entryInfoList.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( entryInfoArray[ index ].isFile( ) )
			result_file_path_vector.emplace_back( entryInfoArray[ index ].absoluteFilePath( ) );
		else
			result_dir_path_vector.emplace_back( entryInfoArray[ index ].absoluteFilePath( ) );
	return true;
}
bool pathTools::getInPathInfoVector( const QString &get_path, std::vector< QString > &result_dir_path_vector, std::vector< QString > &result_file_path_vector ) {
	// 遍历指向
	std::vector< QString > *freachPtr;
	// 子目录指向
	std::vector< QString > *subContrlPtr;
	// 指向交换存储的临时指向
	std::vector< QString > *temp;
	// 返回目录
	std::vector< QString > dirPathVector;
	// 返回文件
	std::vector< QString > filePathVector;
	// 存储遍历目录
	std::vector< QString > findSubPath;
	// 存储下一次遍历目录
	std::vector< QString > nextFindSubPath;
	if( getOnPathInfoVector( get_path, dirPathVector, filePathVector ) == false )
		return false;
	result_dir_path_vector.append_range( dirPathVector );
	result_file_path_vector.append_range( filePathVector );
	freachPtr = &findSubPath;
	subContrlPtr = &nextFindSubPath;
	freachPtr->append_range( dirPathVector );
	size_t count = findSubPath.size( );
	if( count == 0 )
		return true;
	auto findSubPathArray = freachPtr->data( );
	size_t index;

	do {
		for( index = 0; index < count; ++index )
			if( getOnPathInfoVector( findSubPathArray[ index ], dirPathVector, filePathVector ) ) {
				result_dir_path_vector.append_range( dirPathVector );
				result_file_path_vector.append_range( filePathVector );
				subContrlPtr->append_range( dirPathVector );
			}
		count = subContrlPtr->size( );
		if( count == 0 )
			break; // 不需要下次变量
		// 交换指向
		temp = freachPtr;
		freachPtr = subContrlPtr;
		subContrlPtr = temp;
		// 获取遍历起始地址
		findSubPathArray = freachPtr->data( );
		// 清理子目录存储
		subContrlPtr->clear( );
	} while( true );

	return false;
}
