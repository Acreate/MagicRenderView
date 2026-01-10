#include "toColorNode.h"

#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/outputPort/unity/colorOutputPort.h"
#include "../../../../port/outputPort/unity/stringOutputPort.h"

bool ToColorNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< AnyVarInputPort >( tr( "值" ) ) == nullptr )
			return false;
		if( appendOutputPortType< ColorOutputPort >( tr( "颜色" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToColorNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToColorNode::readyNodeRunData( ) {
	return false;
}
bool ToColorNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
