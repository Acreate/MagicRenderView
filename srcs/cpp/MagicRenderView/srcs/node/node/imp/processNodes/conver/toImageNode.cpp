#include "toImageNode.h"

#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/outputPort/unity/imageOutputPort.h"
#include "../../../../port/outputPort/unity/stringOutputPort.h"

bool ToImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< AnyVarInputPort >( tr( "值" ) ) == nullptr )
			return false;
		if( appendOutputPortType< ImageOutputPort >( tr( "图像" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToImageNode::readyNodeRunData( ) {
	return false;
}
bool ToImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
