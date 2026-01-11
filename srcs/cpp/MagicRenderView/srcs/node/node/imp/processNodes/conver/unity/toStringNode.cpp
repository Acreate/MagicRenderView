#include "toStringNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

ToStringNode::ToStringNode( const QString &node_name ) : ProcessNode( node_name ) { outVarPtr = nullptr; }
bool ToStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		anyVarInputPortPtr = appendInputPortType< AnyVarInputPort >( tr( "值" ) );
		if( anyVarInputPortPtr == nullptr )
			return false;
		stringOutputPortPtr = appendOutputPortType< StringOutputPort >( tr( "字符串" ) );
		if( stringOutputPortPtr == nullptr )
			return false;
		if( outVarPtr )
			varDirector->release( outVarPtr );
		if( varDirector->create( outVarPtr ) == false )
			return false;
		if( setPortVar( stringOutputPortPtr, outVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToStringNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToStringNode::readyNodeRunData( ) {
	return false;
}
bool ToStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
