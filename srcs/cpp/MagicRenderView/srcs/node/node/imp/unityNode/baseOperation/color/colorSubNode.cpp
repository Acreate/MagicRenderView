#include "colorSubNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/colorInputPort.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

#include "../../../../../../tools/imageTools.h"

ColorSubNode::ColorSubNode( const QString &node_name ) : UnityNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorSubNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "颜色" ), firstInputPort );
		Def_AppendInputPortType( tr( "颜色" ), secondInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return UnityNode::initEx( parent );

}
bool ColorSubNode::updateLayout( ) {
	if( UnityNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorSubNode::readyNodeRunData( ) {
	return true;
}
bool ColorSubNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
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
	varDirector = outputPortArray[ 0 ]->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	ImageTools::colorOperation::sub( *outputVarPtr, *converInt );

	return true;
}
