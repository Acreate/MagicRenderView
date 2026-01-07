#include "intAddNode.h"

#include "../../../../port/inputPort/unity/intInputPort.h"
#include "../../../../port/outputPort/unity/intOutputPort.h"
bool IntAddNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< IntInputPort >( tr( "被加数" ) ) == nullptr )
			return false;
		if( appendInputPortType< IntInputPort >( tr( "加数" ) ) == nullptr )
			return false;
		if( appendOutputPortType< IntOutputPort >( tr( "和" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool IntAddNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntAddNode::readNodeRunData( ) {
	return true;
}
bool IntAddNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
