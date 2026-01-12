#include "readFileImageNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
#include <qfileinfo.h>

#include "../../../../../director/varDirector.h"
#include "../../../../port/outputPort/outputPort.h"
#include "../../../../port/outputPort/unity/imageOutputPort.h"
ReadFileImageNode::ReadFileImageNode( const QString &node_name ) : ProcessNode( node_name ) {
	outVarPtr = nullptr;
}
bool ReadFileImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		
		if( appendInputPortType( tr( "路径" ), filePathPort ) == false )
			return false;
		if( appendOutputPortType( tr( "图像" ), imageOutputPort ) == false )
			return false;
		if( outVarPtr )
			varDirector->release( outVarPtr );
		if( varDirector->create( outVarPtr ) == false )
			return false;
		if( setPortVar( imageOutputPort, outVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ReadFileImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ReadFileImageNode::readyNodeRunData( ) {
	return false;
}
bool ReadFileImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {

	auto &outputPorts = getRefPort( filePathPort );
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
	outVarPtr->load( redFile.absoluteFilePath( ) );
	return true;
}
