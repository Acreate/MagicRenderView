#include "toStringNode.h"

#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/outputPort/unity/stringOutputPort.h"

bool ToStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< AnyVarInputPort >( tr( "值" ) ) == nullptr )
			return false;
		if( appendOutputPortType< StringOutputPort >( tr( "字符串" ) ) == nullptr )
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
