#include "ifNode.h"

#include "../../../port/inputPort/interface/interFaceInputPort.h"
#include "../../../port/inputPort/point/pointInputPort.h"
#include "../../../port/outputPort/interface/interFaceOutputPort.h"
bool IfNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< PointInputPort >( tr( "定位" ) ) == nullptr )
			return false;
		if( appendInputPortType< InterFaceInputPort >( tr( "判断" ) ) == nullptr )
			return false;
		if( appendOutputPortType< InterFaceOutputPort >( tr( "成立" ) ) == nullptr )
			return false;
		if( appendOutputPortType< InterFaceOutputPort >( tr( "失败" ) ) == nullptr )
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
