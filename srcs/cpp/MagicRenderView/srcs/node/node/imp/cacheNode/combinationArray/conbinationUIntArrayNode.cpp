#include "conbinationUIntArrayNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/intVectorInputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/outputPort/anyVar/anyVarOutputPort.h"
#include "../../../../port/outputPort/array/uIntVectorOutputPort.h"

ConbinationUIntArrayNode::ConbinationUIntArrayNode( const QString &node_name ) : CacheNode( node_name ) {
	outVarPtr = nullptr;
	anyOutputVarPtr = nullptr;
}
bool ConbinationUIntArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType( tr( "无符号整数" ), vectorInputPortPtr ) == false )
			return false;
		if( appendInputPortType( tr( "条件" ), anyVarInputPortPtr ) == false )
			return false;

		if( appendOutputPortType( tr( "无符号整数" ), outputArrayPortPtr ) == false )
			return false;
		if( appendOutputPortType( tr( "条件" ), anyVarOutputPortPtr ) == false )
			return false;
		if( setPortMultiple( vectorInputPortPtr, true ) == false )
			return false;
		return true;
	};
	return CacheNode::initEx( parent );
}
bool ConbinationUIntArrayNode::updateLayout( ) {
	if( CacheNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ConbinationUIntArrayNode::readyNodeRunData( ) {
	return true;
}

bool ConbinationUIntArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	if( outVarPtr )
		varDirector->release( outVarPtr );
	if( varDirector->create( outVarPtr ) == false )
		return false;
	if( setPortVar( outputArrayPortPtr, outVarPtr ) == false )
		return false;
	if( setPortVar( anyVarOutputPortPtr, anyOutputVarPtr ) == false )
		return false;
	return true;
}
