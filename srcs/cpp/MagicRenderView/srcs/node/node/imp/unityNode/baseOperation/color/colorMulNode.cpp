#include "colorMulNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/colorInputPort.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

#include "../../../../../../tools/imageTools.h"

ColorMulNode::ColorMulNode( const QString &node_name ) : UnityNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorMulNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType( tr( "整数" ), firstInputPort ) == false )
			return false;
		if( appendInputPortType( tr( "整数列表" ), secondInputPort ) == false )
			return false;
		if( appendOutputPortType( tr( "结果" ), outputPort ) == false )
			return false;
		if( outputVarPtr )
			varDirector->release( outputVarPtr );
		if( varDirector->create( outputVarPtr ) == false )
			return false;
		if( setPortVar( outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return UnityNode::initEx( parent );

}
bool ColorMulNode::updateLayout( ) {
	if( UnityNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorMulNode::readyNodeRunData( ) {
	return true;
}
bool ColorMulNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	OutputPort *const*outputPortArray;
	size_t count;
	NodeType *converInt;
	void *portVarPtr;
	VarDirector *varDirector;
	const std::vector< OutputPort * > *outputPorts = &getRefPort( firstInputPort );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	varDirector = outputPortArray[ 0 ]->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	*outputVarPtr = *converInt;
	outputPorts = &getRefPort( secondInputPort );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	varDirector =  outputPortArray[ 0 ]->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	ImageTools::colorOperation::mul( *outputVarPtr, *converInt );

	return true;
}
