#include "startNode.h"

#include <qdatetime.h>

#include "../../../../app/application.h"
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
		return true;
	};

	return BeginNode::initEx( parent );
}

bool StartNode::updateLayout( ) {
	if( BeginNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StartNode::readNextBeginNodeData( ) {
	readUpdate = true;
	return true;
}
bool StartNode::readNodeRunData( ) {
	mSecsSinceEpoch = 0;
	return true;
}
bool StartNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector ) {
	return true;
}
bool StartNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	if( mSecsSinceEpoch != 0 || readUpdate == false )
		return true;
	readUpdate = true;
	mSecsSinceEpoch = QDateTime::currentDateTime( ).toMSecsSinceEpoch( );
	mSecsSinceEpoch = mSecsSinceEpoch - ndoe_run_start_data_time.toMSecsSinceEpoch( );
	return true;
}
bool StartNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
