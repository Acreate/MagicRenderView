#include "ifNode.h"

#include "../../../port/inputPort/unity/intInputPort.h"
#include "../../../port/outputPort/interface/interFaceOutputPort.h"
bool IfNode::updateLayout( ) {
	if( LogicNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IfNode::init( DrawNodeWidget *parent ) {
	if( LogicNode::init( parent ) == false )
		return false;
	if( appendInputPortType< IntInputPort >( tr( "判断依据" ) ) == nullptr )
		return false;
	if( appendOutputPortType< InterFaceOutputPort >( tr( "依据成立-过程转移" ) ) == nullptr )
		return false;
	if( appendOutputPortType< InterFaceOutputPort >( tr( "依据失败-过程转移" ) ) == nullptr )
		return false;
	return true;
}
