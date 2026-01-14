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
		Def_AppendInputPortType( tr( "路径" ), filePathPort );
		Def_AppendBindVarOutputPortType( tr( "图像" ), imageOutputPort, outVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ReadFileImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool ReadFileImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {

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
