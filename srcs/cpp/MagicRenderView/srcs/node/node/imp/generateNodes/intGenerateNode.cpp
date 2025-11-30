#include "intGenerateNode.h"

#include "../../../port/inputPort/any/anyInputPort.h"
#include "../../../port/outputPort/array/intVectorOutputPort.h"

bool IntGenerateNode::init( DrawNodeWidget *parent, NodeRefLinkInfo *node_ref_link_info ) {
	if( GenerateNode::init( parent, node_ref_link_info ) == false )
		return false;
	if( appendInputPortType< AnyInputPort >( tr( "过程接入" ) ) == nullptr )
		return false;
	if( appendOutputPortType< IntVectorOutputPort >( tr( "导出生成整数序列" ) ) == nullptr )
		return false;
	return true;

}
bool IntGenerateNode::updateLayout( ) {
	if( GenerateNode::updateLayout( ) == false )
		return false;
	return true;
}
