#include "writeFileImageNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
#include <qfile.h>
#include <__msvc_filebuf.hpp>

#include "../../../../../director/varDirector.h"
#include "../../../../../tools/pathTools.h"
#include "../../../../nodeTools/nodeTools.h"
#include "../../../../port/inputPort/unity/imageInputPort.h"
#include "../../../../port/outputPort/outputPort.h"
bool WriteFileImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "路径" ), writeFilePathPort ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "写入内容" ), writeImagePort ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool WriteFileImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool WriteFileImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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

	wirteFileRefPort = nodeToolsPtr->getRefPort( writeImagePort );
	count = wirteFileRefPort->size( );
	if( count == 0 )
		return true;
	wrietFilePathPort = wirteFileRefPort->data( )[ 0 ];
	varDirector = wrietFilePathPort->getVarDirector( );
	varPtr = wrietFilePathPort->getVarPtr( );
	QImage *data;
	if( varDirector->cast_ptr( varPtr, data ) == false )
		return true;
	data->save( *filePath, ".png" );
	return true;
}
