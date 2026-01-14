#include "writeFileImageNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
#include <qfile.h>
#include <__msvc_filebuf.hpp>

#include "../../../../../director/varDirector.h"
#include "../../../../../tools/path.h"
#include "../../../../port/inputPort/unity/imageInputPort.h"
#include "../../../../port/outputPort/outputPort.h"
bool WriteFileImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "路径" ), writeFilePathPort );
		Def_AppendInputPortType( tr( "写入内容" ), writeImagePort );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool WriteFileImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool WriteFileImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	auto &wirteFileRefPort = getRefPort( writeFilePathPort );
	size_t count = wirteFileRefPort.size( );
	if( count == 0 )
		return true;
	auto &writeBinRefPorts = getRefPort( writeImagePort );
	count = writeBinRefPorts.size( );
	if( count == 0 )
		return true;
	auto wrietFilePathPort = wirteFileRefPort.data( )[ 0 ];
	auto varDirector = wrietFilePathPort->getVarDirector( );
	auto varPtr = wrietFilePathPort->getVarPtr( );
	QString *filePath;
	if( varDirector->cast_ptr( varPtr, filePath ) == false )
		return true;
	if( path::createFile( *filePath ) == false )
		return true;
	auto wrietBinVector = writeBinRefPorts.data( )[ 0 ];
	varDirector = wrietBinVector->getVarDirector( );
	varPtr = wrietBinVector->getVarPtr( );
	QImage *data;
	if( varDirector->cast_ptr( varPtr, data ) == false )
		return true;
	data->save( *filePath, ".png" );
	return true;
}
