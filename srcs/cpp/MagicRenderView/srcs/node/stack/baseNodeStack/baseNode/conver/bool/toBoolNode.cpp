#include "toBoolNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/binOutputPort.h>

#include <node/nodeTools/nodeTools.h>

#include "../../../../../../tools/varDirectorTools.h"
#include "../../../../../port/outputPort/unity/boolOutputPort.h"
ToBoolNode::ToBoolNode( const QString &node_name ) : ProcessNode( node_name ) { outVarPtr = nullptr; }
bool ToBoolNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "值" ), anyVarInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "逻辑" ), binOutputPortPtr, outVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToBoolNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool ToBoolNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	*outVarPtr = false;
	auto outputPorts = nodeToolsPtr->getRefPort( anyVarInputPortPtr );
	if( outputPorts->size( ) == 0 )
		return true;
	auto outputPort = outputPorts->data( )[ 0 ];
	*outVarPtr = VarDirectorTools::isTrue( outputPort->getVarDirector( ), outputPort->getVarPtr( ) );
	return true;
}
