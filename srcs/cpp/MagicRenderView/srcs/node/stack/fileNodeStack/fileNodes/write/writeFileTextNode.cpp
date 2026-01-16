#include "writeFileTextNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
#include <qfile.h>

#include "../../../../../director/varDirector.h"
#include "../../../../../tools/path.h"
#include "../../../../nodeTools/nodeTools.h"
#include "../../../../port/outputPort/outputPort.h"
bool WriteFileTextNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "路径" ), writeFilePathPort ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "写入内容" ), writeTextPort ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool WriteFileTextNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool WriteFileTextNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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
	if( path::createFile( *filePath ) == false )
		return true;

	wirteFileRefPort = nodeToolsPtr->getRefPort( writeTextPort );
	count = wirteFileRefPort->size( );
	if( count == 0 )
		return true;
	wrietFilePathPort = wirteFileRefPort->data( )[ 0 ];
	varDirector = wrietFilePathPort->getVarDirector( );
	varPtr = wrietFilePathPort->getVarPtr( );
	QString *data;
	if( varDirector->cast_ptr( varPtr, data ) == false )
		return true;
	QFile file( *filePath );
	if( file.open( QIODeviceBase::ReadWrite ) == false )
		return true;
	auto byteArray = data->toUtf8( );
	file.write( byteArray.data( ), byteArray.size( ) );
	return true;
}
