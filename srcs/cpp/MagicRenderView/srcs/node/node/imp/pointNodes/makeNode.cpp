#include "makeNode.h"

#include "../../../port/outputPort/interface/interFaceOutputPort.h"

bool MakeNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendOutputPortType< InterFaceOutputPort >( tr( "过程转移" ) ) == nullptr )
			return false;
		return true;
	};
	return PointNode::initEx( parent );
}
bool MakeNode::updateLayout( ) {
	if( PointNode::updateLayout( ) == false )
		return false;
	return true;
}
