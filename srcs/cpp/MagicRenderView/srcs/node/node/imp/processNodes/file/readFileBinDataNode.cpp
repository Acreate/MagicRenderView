#include "readFileBinDataNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
#include <qfileinfo.h>

#include "../../../../../director/varDirector.h"
#include "../../../../port/outputPort/array/binVectorOutputPort.h"
#include "../../../../port/outputPort/unity/uIntOutputPort.h"
ReadFileBinDataNode::ReadFileBinDataNode( const QString &node_name ) : ProcessNode( node_name ) {
	outVectorCountPtr = nullptr;
	outVectorPtr = nullptr;
}
bool ReadFileBinDataNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType( tr( "路径" ), filePathInputPort ) == false )
			return false;
		if( appendOutputPortType( tr( "二进制" ), this->outBinVectorPort ) == false )
			return false;
		if( appendOutputPortType( tr( "二进制" ), this->outVectorCountPort ) == false )
			return false;
		if( outVectorPtr )
			varDirector->release( outVectorPtr );
		if( varDirector->create( outVectorPtr ) == false )
			return false;
		if( outVectorCountPtr )
			varDirector->release( outVectorCountPtr );
		if( varDirector->create( outVectorCountPtr ) == false )
			return false;
		if( setPortVar( outBinVectorPort, outVectorPtr ) == false )
			return false;
		if( setPortVar( outVectorCountPort, outVectorCountPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ReadFileBinDataNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ReadFileBinDataNode::readyNodeRunData( ) {
	return true;
}
bool ReadFileBinDataNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	outVectorPtr->clear( );
	*outVectorCountPtr = 0;
	auto &outputPorts = getRefPort( filePathInputPort );
	size_t count = outputPorts.size( );
	if( count == 0 )
		return true;
	auto outputPortArrayPtr = outputPorts.data( );
	auto varDirector = outputPortArrayPtr[ 0 ]->getVarDirector( );
	auto varPtr = outputPortArrayPtr[ 0 ]->getVarPtr( );
	QString *resultFilePth;
	if( varDirector->cast_ptr( varPtr, resultFilePth ) == false )
		return true;
	QFileInfo redFile( *resultFilePth );
	if( redFile.exists( ) == false )
		return true;
	QFile file( redFile.absoluteFilePath( ) );
	if( file.open( QIODeviceBase::ReadWrite ) == false )
		return true;
	auto readAll = file.readAll( );
	*outVectorCountPtr = readAll.size( );
	if( *outVectorCountPtr == 0 )
		return true;
	outVectorPtr->resize( *outVectorCountPtr );
	char *sourceData = readAll.data( );
	auto destData = outVectorPtr->data( );
	for( count = 0; count < *outVectorCountPtr; ++count )
		destData[ count ] = sourceData[ count ];
	return true;
}
