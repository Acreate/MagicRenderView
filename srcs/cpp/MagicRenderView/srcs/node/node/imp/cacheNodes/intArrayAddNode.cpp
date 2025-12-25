#include "intArrayAddNode.h"

#include "../../../port/inputPort/array/intVectorInputPort.h"
#include "../../../port/inputPort/unity/intInputPort.h"
#include "../../../port/outputPort/unity/intOutputPort.h"

bool IntArrayAddNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< IntVectorInputPort >( tr( "整数" ) ) == nullptr )
			return false;
		if( appendOutputPortType< IntOutputPort >( tr( "整数和" ) ) == nullptr )
			return false;
		return true;
	};
	return ArrayNode::initEx( parent );
}
bool IntArrayAddNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
