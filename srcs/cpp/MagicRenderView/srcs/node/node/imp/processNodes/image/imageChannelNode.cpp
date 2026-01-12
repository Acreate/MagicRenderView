#include "imageChannelNode.h"

#include <functional>
#include <qmetatype.h>
#include <node/node/node.h>
#include <node/node/processNode.h>

#include "../../../../../director/varDirector.h"
#include "../../../../port/inputPort/unity/imageInputPort.h"
#include "../../../../port/outputPort/array/colorVectorOutputPort.h"

ImageChannelNode::ImageChannelNode( const QString &node_name ) : ProcessNode( node_name ) {
	redOutVectorVarPtr = nullptr;
	greenOutVectorVarPtr = nullptr;
	blueOutVectorVarPtr = nullptr;
	alphaOutVectorVarPtr = nullptr;
}
bool ImageChannelNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( appendInputPortType< >( tr( "输出" ), imageInputPortPtr ) == false )
			return false;
		if( appendOutputPortType< >( tr( "红色" ), redOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "绿色" ), greenOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "蓝色" ), blueOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "透明" ), alphaOutputPort ) == false )
			return false;
		if( redOutVectorVarPtr )
			varDirector->release( redOutVectorVarPtr );
		if( varDirector->create( redOutVectorVarPtr ) == false )
			return false;
		if( greenOutVectorVarPtr )
			varDirector->release( greenOutVectorVarPtr );
		if( varDirector->create( greenOutVectorVarPtr ) == false )
			return false;
		if( blueOutVectorVarPtr )
			varDirector->release( blueOutVectorVarPtr );
		if( varDirector->create( blueOutVectorVarPtr ) == false )
			return false;
		if( alphaOutVectorVarPtr )
			varDirector->release( alphaOutVectorVarPtr );
		if( varDirector->create( alphaOutVectorVarPtr ) == false )
			return false;
		if( setPortVar( redOutputPort, redOutVectorVarPtr ) == false )
			return false;
		if( setPortVar( greenOutputPort, greenOutVectorVarPtr ) == false )
			return false;
		if( setPortVar( blueOutputPort, blueOutVectorVarPtr ) == false )
			return false;
		if( setPortVar( alphaOutputPort, alphaOutVectorVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ImageChannelNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ImageChannelNode::readyNodeRunData( ) {
	return true;
}
bool ImageChannelNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
