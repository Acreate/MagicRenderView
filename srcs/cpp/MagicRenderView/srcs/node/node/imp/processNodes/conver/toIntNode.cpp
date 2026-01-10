#include "toIntNode.h"

#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/outputPort/unity/intOutputPort.h"
#include "../../../../port/outputPort/unity/stringOutputPort.h"

bool ToIntNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< AnyVarInputPort >( tr( "值" ) ) == nullptr )
			return false;
		if( appendOutputPortType< IntOutputPort >( tr( "整数" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToIntNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToIntNode::readyNodeRunData( ) {
	return false;
}
bool ToIntNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
