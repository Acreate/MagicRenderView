#include "writeFileBinDataNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
#include <qfileinfo.h>

#include "../../../../../director/varDirector.h"
#include "../../../../../tools/path.h"
#include "../../../../port/inputPort/array/binVectorInputPort.h"
#include "../../../../port/outputPort/outputPort.h"
bool WriteFileBinDataNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "路径" ), writeFilePathPort );
		Def_AppendInputPortType( tr( "写入内容" ), writeBinVectorPort );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool WriteFileBinDataNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool WriteFileBinDataNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	auto &wirteFileRefPort = getRefPort( writeFilePathPort );
	size_t count = wirteFileRefPort.size( );
	if( count == 0 )
		return true;
	auto &writeBinRefPorts = getRefPort( writeBinVectorPort );
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
	std::vector< uint8_t > *data;
	if( varDirector->cast_ptr( varPtr, data ) == false )
		return true;
	QFile file( *filePath );
	if( file.open( QIODeviceBase::ReadWrite ) == false )
		return true;
	file.write( ( const char * ) data->data( ), data->size( ) );
	return true;
}
