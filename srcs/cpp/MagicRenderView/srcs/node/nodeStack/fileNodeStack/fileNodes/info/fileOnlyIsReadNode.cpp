#include "fileOnlyIsReadNode.h"

#include <app/application.h>
#include <director/varDirector.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/boolOutputPort.h>
#include <QDir>
#include <qfileinfo.h>
#include <tools/infoTool.h>

Def_Entity_NodeTypeName_Function( FileOnlyIsReadNode, Node::tr( "文件信息/是否只读" ) );

FileOnlyIsReadNode::FileOnlyIsReadNode( const QString &node_name ) : ProcessNode( node_name ) {

	outIsOnlyReadPtr = nullptr;
}
bool FileOnlyIsReadNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "文件路径" ), filePtahInputPortPtr ) == false )
			return false;

		if( nodeToolsPtr->appendOutputPortType( this, tr( "只读" ), isOnlyReadOutputPortPtr, outIsOnlyReadPtr ) == false )
			return false;

		return true;
	};
	return ProcessNode::initEx( parent );
}
bool FileOnlyIsReadNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool FileOnlyIsReadNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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
	if( fileInfo.exists( ) == false ) {
		*outIsOnlyReadPtr = true;
		return true;
	}
	*outIsOnlyReadPtr = fileInfo.isReadable( ) == false;
	return true;
}
