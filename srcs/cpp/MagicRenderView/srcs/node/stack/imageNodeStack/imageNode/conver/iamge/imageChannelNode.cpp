#include "imageChannelNode.h"

#include <director/varDirector.h>
#include <functional>
#include <node/node/node.h>
#include <node/node/processNode.h>
#include <node/port/inputPort/unity/imageInputPort.h>
#include <node/port/outputPort/array/colorVectorOutputPort.h>


ImageChannelNode::ImageChannelNode( const QString &node_name ) : ProcessNode( node_name ) {
	redOutVectorVarPtr = nullptr;
	greenOutVectorVarPtr = nullptr;
	blueOutVectorVarPtr = nullptr;
	alphaOutVectorVarPtr = nullptr;
}
bool ImageChannelNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "图像" ), imageInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "红色" ), redOutputPort, redOutVectorVarPtr );
		Def_AppendBindVarOutputPortType( tr( "绿色" ), greenOutputPort, greenOutVectorVarPtr );
		Def_AppendBindVarOutputPortType( tr( "蓝色" ), blueOutputPort, blueOutVectorVarPtr );
		Def_AppendBindVarOutputPortType( tr( "透明" ), alphaOutputPort, alphaOutVectorVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ImageChannelNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool ImageChannelNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
