#include "ifNode.h"

#include "../../../port/inputPort/unity/intInputPort.h"
#include "../../../port/outputPort/interface/interFaceOutputPort.h"
bool IfNode::initEx( DrawNodeWidget *parent ) {
	initExCallFunction = [this] ( DrawNodeWidget *draw_node_widget ) {
		if( appendInputPortType< IntInputPort >( tr( "判断依据" ) ) == nullptr )
			return false;
		if( appendOutputPortType< InterFaceOutputPort >( tr( "依据成立-过程转移" ) ) == nullptr )
			return false;
		if( appendOutputPortType< InterFaceOutputPort >( tr( "依据失败-过程转移" ) ) == nullptr )
			return false;
		return true;
	};
	return LogicNode::initEx( parent );

}
bool IfNode::updateLayout( ) {
	if( LogicNode::updateLayout( ) == false )
		return false;
	return true;
}
