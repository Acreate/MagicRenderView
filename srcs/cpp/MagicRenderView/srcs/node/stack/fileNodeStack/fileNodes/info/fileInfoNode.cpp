#include "fileInfoNode.h"

#include <app/application.h>
#include <director/varDirector.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/dateTimeOutputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <node/port/outputPort/unity/uIntOutputPort.h>
#include <QDir>
#include <qfileinfo.h>
#include <tools/infoTool.h>

FileInfoNode::FileInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	outFilePtahPtr = nullptr;
	outDirNamePtr = nullptr;
	outBaseNamePtr = nullptr;
	outAuthorNamePtr = nullptr;
	outCreateTimePtr = nullptr;
	outLastChangeTimePtr = nullptr;
	outFileSizePtr = nullptr;
	outIsOnlyReadPtr = nullptr;
	outIsExisPtr = nullptr;
	outLastReadTimePtr = nullptr;
	outisFilePtr = nullptr;
}
bool FileInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "文件路径" ), filePtahInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "绝对路径" ), filePtahOutputPortPtr, outFilePtahPtr );
		Def_AppendBindVarOutputPortType( tr( "目录路径" ), dirNameOutputPortPtr, outDirNamePtr );
		Def_AppendBindVarOutputPortType( tr( "基本名称" ), baseNameOutputPortPtr, outBaseNamePtr );
		Def_AppendBindVarOutputPortType( tr( "作者" ), authorNameOutputPortPtr, outAuthorNamePtr );
		Def_AppendBindVarOutputPortType( tr( "创建时间" ), createTimeOutputPortPtr, outCreateTimePtr );
		Def_AppendBindVarOutputPortType( tr( "最后阅读" ), lastReadTimeOutputPortPtr, outLastReadTimePtr );
		Def_AppendBindVarOutputPortType( tr( "最后时间" ), lastChangeTimeOutputPortPtr, outLastChangeTimePtr );
		Def_AppendBindVarOutputPortType( tr( "大小" ), fileSizeOutputPortPtr, outFileSizePtr );
		Def_AppendBindVarOutputPortType( tr( "只读" ), isOnlyReadOutputPortPtr, outIsOnlyReadPtr );
		Def_AppendBindVarOutputPortType( tr( "存在" ), isExisOutputPortPtr, outIsExisPtr );
		Def_AppendBindVarOutputPortType( tr( "是否为文件" ), isFileOutputPortPtr, outisFilePtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool FileInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool FileInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	auto outputPorts = nodeToolsPtr->getRefPort( filePtahInputPortPtr );
	if( outputPorts->size( ) == 0 )
		return true;
	auto outputPort = outputPorts->data( )[ 0 ];
	auto varDirector = outputPort->getVarDirector( );
	if( varDirector == nullptr )
		return true;
	auto varPtr = outputPort->getVarPtr( );
	if( varPtr == nullptr )
		return true;
	QString *path;
	if( varDirector->cast_ptr( varPtr, path ) == false )
		return true;
	QFileInfo fileInfo( *path );
	*outFilePtahPtr = fileInfo.absoluteFilePath( );
	*outDirNamePtr = fileInfo.absoluteDir( ).absolutePath( );
	*outBaseNamePtr = fileInfo.baseName( );
	if( fileInfo.exists( ) == false ) {
		*outIsExisPtr = false;
		*outIsOnlyReadPtr = true;
		outAuthorNamePtr->clear( );
		*outCreateTimePtr = QDateTime::fromMSecsSinceEpoch( 0 );
		*outLastChangeTimePtr = QDateTime::fromMSecsSinceEpoch( 0 );
		*outLastReadTimePtr = QDateTime::fromMSecsSinceEpoch( 0 );
		return true;
	}
	*outIsExisPtr = true;
	*outIsOnlyReadPtr = fileInfo.isReadable( ) == false;
	outAuthorNamePtr->clear( );
	*outCreateTimePtr = fileInfo.birthTime( );
	*outLastChangeTimePtr = fileInfo.lastModified( );
	*outLastReadTimePtr = fileInfo.lastRead( );
	if( fileInfo.isDir( ) )
		*outisFilePtr = false;
	else
		*outisFilePtr = true;
	return true;
}
