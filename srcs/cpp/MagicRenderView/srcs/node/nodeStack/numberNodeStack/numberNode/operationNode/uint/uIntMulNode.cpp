#include "uIntMulNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/uIntInputPort.h>
#include <node/port/outputPort/unity/uIntOutputPort.h>

#include <node/nodeTools/nodeComponentControl.h>

Def_Entity_NodeTypeName_Function( UIntMulNode, Node::tr( "运算/单元/无符号整数/乘法" ) );

UIntMulNode::UIntMulNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool UIntMulNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeComponentControlPtr->appendInputPortType( this, tr( "无符号整数" ), firstInputPort ) == false )
			return false;
		if( nodeComponentControlPtr->appendInputPortType( this, tr( "无符号整数" ), secondInputPort ) == false )
			return false;
		if( nodeComponentControlPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool UIntMulNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntMulNode::readyNodeRunData( ) {
	return true;
}
bool UIntMulNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	OutputPort *const*outputPortArray;
	size_t count;
	NodeType *converInt;
	void *portVarPtr;
	VarDirector *varDirector;
	const std::vector< OutputPort * > *outputPorts = nodeComponentControlPtr->getRefPort( firstInputPort );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	varDirector = outputPortArray[ 0 ]->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	*outputVarPtr = *converInt;
	outputPorts = nodeComponentControlPtr->getRefPort( secondInputPort );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	varDirector = outputPortArray[ 0 ]->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	*outputVarPtr *= *converInt;

	return true;
}
