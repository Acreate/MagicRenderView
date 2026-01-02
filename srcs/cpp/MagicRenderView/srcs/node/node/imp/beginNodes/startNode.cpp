#include "startNode.h"

#include "../../../nodeRunInfo/nodeInfo/nodeBuilderInfo.h"
#include "../../../nodeRunInfo/port/outputPort/outputPortBuilderInfo.h"
#include "../../../port/outputPort/begin/beginOutputPort .h"
#include "../../../port/outputPort/toBegin/toBeginOutputPort.h"

bool StartNode::initEx( MainWidget *parent ) {

	initExCallFunction = [this] ( MainWidget *main_widget ) {
		auto beginOutputPort = appendOutputPortType< BeginOutputPort >( tr( "过程开始" ) );
		if( beginOutputPort == nullptr )
			return false;
		auto toBeginOutputPort = appendOutputPortType< ToBeginOutputPort >( tr( "过程返回" ) );
		if( toBeginOutputPort == nullptr )
			return false;
		auto nodeCallFucntion = [beginOutputPort, this] ( std::vector< InputPortBuilderInfo * > &input_port_builder_infos, std::vector< OutputPortBuilderInfo * > &output_port_builder_infos, std::vector< NodeBuilderInfo * > &node_builder_infos ) {
			auto outputPortBuilderInfo = getOutputPortBuilderInfo( beginOutputPort );
			if( outputPortBuilderInfo->call( node_builder_infos ) == false )
				return false;
			return true;
		};
		nodeBuilderInfo->init( nodeCallFucntion );
		return true;
	};

	return BeginNode::initEx( parent );
}

bool StartNode::updateLayout( ) {
	if( BeginNode::updateLayout( ) == false )
		return false;
	return true;
}
