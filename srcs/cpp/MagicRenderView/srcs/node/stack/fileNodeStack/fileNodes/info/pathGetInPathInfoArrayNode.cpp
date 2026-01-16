#include "pathGetInPathInfoArrayNode.h"

#include <app/application.h>
#include <tools/infoTool.h>

#include "../../../../../director/varDirector.h"
#include "../../../../../tools/path.h"
#include "../../../../nodeTools/nodeTools.h"
#include "../../../../port/inputPort/unity/stringInputPort.h"
#include "../../../../port/outputPort/array/stringVectorOutputPort.h"

PathGetInPathInfoArrayNode::PathGetInPathInfoArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	pathSubPathOutputVarPtr = nullptr;
	dirPathOutputVarPtr = nullptr;
	filePathOutputVarPtr = nullptr;
}
bool PathGetInPathInfoArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "路径" ), pathInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "路径下的文件与目录" ), pathSubPathOutputPortPtr, pathSubPathOutputVarPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "路径下的目录" ), dirPathOutputPortPtr, dirPathOutputVarPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "路径下的文件" ), filePathOutputPortPtr, filePathOutputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool PathGetInPathInfoArrayNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool PathGetInPathInfoArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	dirPathOutputVarPtr->clear( );
	filePathOutputVarPtr->clear( );
	pathSubPathOutputVarPtr->clear( );
	auto outputPorts = nodeToolsPtr->getRefPort( pathInputPortPtr );
	size_t count = outputPorts->size( );
	if( count == 0 )
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
	if( path::getInPathInfoVector( *path, *dirPathOutputVarPtr, *filePathOutputVarPtr ) == false )
		return true;
	pathSubPathOutputVarPtr->append_range( *dirPathOutputVarPtr );
	pathSubPathOutputVarPtr->append_range( *filePathOutputVarPtr );
	return true;
}
