#include "debugNodeInfoWidget.h"

#include "../../../../port/inputPort/inputPort.h"
#include "../../../../port/outputPort/outputPort.h"
#include "../../debugNodes/outInfo/debugInfoNode.h"
#include "contentWidget/debugNodeContentWidget.h"
#include "contentWidget/outPortItemScorllArea/outPortItemScorllWidget.h"
#include "debugNodeEditorNodeInfoScrollArea.h"

DebugNodeInfoWidget::DebugNodeInfoWidget( DebugInfoNode *debug_info_node ) : NodeInfoWidget( ), debugInfoNode( debug_info_node ) {
	editorNodeInfoScrollArea = debugNodeEditorScrallArea = new DebugNodeEditorNodeInfoScrollArea( this );
	auto debugNodeContentWidget = debugNodeEditorScrallArea->getDebugNodeContentWidget( );

	outPortItemScorllWidget = debugNodeContentWidget->getOutPortItemScorllWidget( );
}
bool DebugNodeInfoWidget::appendPortInfoMsg( OutputPort *output_port_ptr, const QString &msg ) {
	return outPortItemScorllWidget->appendOutputItem( output_port_ptr, msg );
}
bool DebugNodeInfoWidget::clear( ) {
	return outPortItemScorllWidget->clear( );
}
bool DebugNodeInfoWidget::checkNodeValid( Node *check_node_ptr ) {
	if( ( void * ) debugInfoNode != ( void * ) check_node_ptr )
		return false;
	return debugInfoNode != nullptr;
}
bool DebugNodeInfoWidget::initNodeInfo( Node *check_node_ptr ) {
	if( debugInfoNode == nullptr || ( void * ) debugInfoNode != ( void * ) check_node_ptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( debugInfoNode ) == false )
		return false;
	clear( );
	return true;
}
