#include "fileBaseNameNode.h"

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

Def_Entity_NodeTypeName_Function( FileBaseNameNode, Node::tr( "文件信息/基础名称" ) );

FileBaseNameNode::FileBaseNameNode( const QString &node_name ) : ProcessNode( node_name ) {
	outBaseNamePtr = nullptr;
}
bool FileBaseNameNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "文件路径" ), filePtahInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "基本名称" ), baseNameOutputPortPtr, outBaseNamePtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool FileBaseNameNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool FileBaseNameNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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
	*outBaseNamePtr = fileInfo.baseName( );
	return true;
}
