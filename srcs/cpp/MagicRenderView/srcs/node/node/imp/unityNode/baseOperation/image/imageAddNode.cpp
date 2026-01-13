#include "imageAddNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/imageInputPort.h>
#include <node/port/outputPort/unity/imageOutputPort.h>

#include "../../../../../../tools/imageTools.h"

ImageAddNode::ImageAddNode( const QString &node_name ) : UnityNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ImageAddNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "图像" ), firstInputPort );
		Def_AppendInputPortType( tr( "图像" ), secondInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return UnityNode::initEx( parent );

}
bool ImageAddNode::updateLayout( ) {
	if( UnityNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ImageAddNode::readyNodeRunData( ) {
	return true;
}
bool ImageAddNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
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
	ImageTools::imageOperation::add( *outputVarPtr, *converInt );
	return true;
}
