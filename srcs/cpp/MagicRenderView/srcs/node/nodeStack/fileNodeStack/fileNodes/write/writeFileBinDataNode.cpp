#include "writeFileBinDataNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
#include <qfileinfo.h>

#include "../../../../../director/varDirector.h"
#include "../../../../../tools/pathTools.h"
#include "../../../../nodeTools/nodeTools.h"
#include "../../../../port/inputPort/array/binVectorInputPort.h"
#include "../../../../port/outputPort/outputPort.h"

Def_Entity_NodeTypeName_Function( WriteFileBinDataNode, Node::tr( "写入文件/二进制" ) );

bool WriteFileBinDataNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "路径" ), writeFilePathPort ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "写入内容" ), writeBinVectorPort ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool WriteFileBinDataNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool WriteFileBinDataNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	auto wirteFileRefPort = nodeToolsPtr->getRefPort( writeFilePathPort );
	size_t count = wirteFileRefPort->size( );
	if( count == 0 )
		return true;
	auto wrietFilePathPort = wirteFileRefPort->data( )[ 0 ];
	auto varDirector = wrietFilePathPort->getVarDirector( );
	auto varPtr = wrietFilePathPort->getVarPtr( );
	QString *filePath;
	if( varDirector->cast_ptr( varPtr, filePath ) == false )
		return true;
	if( pathTools::createFile( *filePath ) == false )
		return true;

	wirteFileRefPort = nodeToolsPtr->getRefPort( writeBinVectorPort );
	count = wirteFileRefPort->size( );
	if( count == 0 )
		return true;
	wrietFilePathPort = wirteFileRefPort->data( )[ 0 ];
	varDirector = wrietFilePathPort->getVarDirector( );
	varPtr = wrietFilePathPort->getVarPtr( );
	std::vector< uint8_t > *data;
	if( varDirector->cast_ptr( varPtr, data ) == false )
		return true;
	QFile file( *filePath );
	if( file.open( QIODeviceBase::ReadWrite ) == false )
		return true;
	file.write( ( const char * ) data->data( ), data->size( ) );
	return true;
}
