#include "toUIntNode.h"

#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/outputPort/unity/stringOutputPort.h"
#include "../../../../port/outputPort/unity/uIntOutputPort.h"

bool ToUIntNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< AnyVarInputPort >( tr( "值" ) ) == nullptr )
			return false;
		if( appendOutputPortType< UIntOutputPort >( tr( "无符号整数" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToUIntNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToUIntNode::readyNodeRunData( ) {
	return false;
}
bool ToUIntNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
