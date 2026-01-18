#include "runToTargetNodeBuilderAction.h"

#include "../../../../../director/builderDirector.h"
#include "../../../../../node/node/node.h"
#include "../../../../../win/mainWindow.h"
void RunToTargetNodeBuilderAction::releaTarget( Node *release_target, const SrackInfo &srack_info ) {
	if( release_target == targetNode )
		targetNode = nullptr;
	disconnect( release_target, &Node::release_node_signal, this, &RunToTargetNodeBuilderAction::releaTarget );
}
bool RunToTargetNodeBuilderAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	targetNode = nullptr;
	setInitVarNumber( tr( "未匹配节点" ) );
	return true;
}
bool RunToTargetNodeBuilderAction::run( MainWindow *parent ) {
	return builderDirector->builderNodeProject( );
}
void RunToTargetNodeBuilderAction::setTargetNode( Node *target_node ) {

	if( target_node ) {
		setInitVarNumber( tr( "运行到[%1]" ).arg( target_node->toQString( ) ) );
		if( targetNode ) // 取消旧的信号
			disconnect( targetNode, &Node::release_node_signal, this, &RunToTargetNodeBuilderAction::releaTarget );
		targetNode = target_node; // 赋值，并且增加新的信号
		connect( targetNode, &Node::release_node_signal, this, &RunToTargetNodeBuilderAction::releaTarget );
	} else
		setInitVarNumber( tr( "未匹配节点" ) );
}
