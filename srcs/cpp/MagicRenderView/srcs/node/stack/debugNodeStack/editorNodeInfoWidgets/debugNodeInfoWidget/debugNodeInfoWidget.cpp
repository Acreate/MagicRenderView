#include "debugNodeInfoWidget.h"

#include "../../debugNodes/outInfo/debugInfoNode.h"
DebugNodeInfoWidget::DebugNodeInfoWidget( ) { }
bool DebugNodeInfoWidget::checkNodeValid( Node *check_node_ptr ) {
	debugInfoNode = qobject_cast< DebugInfoNode * >( check_node_ptr );
	return debugInfoNode != nullptr;
}
bool DebugNodeInfoWidget::initNodeInfo( Node *check_node_ptr ) {
	if( debugInfoNode != check_node_ptr )
		debugInfoNode = qobject_cast< DebugInfoNode * >( check_node_ptr );
	if( debugInfoNode == nullptr )
		return false;
	return true;
}
