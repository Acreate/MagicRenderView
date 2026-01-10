#include "toFloatNode.h"

#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/outputPort/unity/floatOutputPort.h"
#include "../../../../port/outputPort/unity/stringOutputPort.h"

bool ToFloatNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< AnyVarInputPort >( tr( "值" ) ) == nullptr )
			return false;
		if( appendOutputPortType< FloatOutputPort >( tr( "浮点" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToFloatNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToFloatNode::readyNodeRunData( ) {
	return false;
}
bool ToFloatNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
