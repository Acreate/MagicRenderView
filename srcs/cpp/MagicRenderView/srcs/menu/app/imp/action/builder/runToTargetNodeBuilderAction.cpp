#include "runToTargetNodeBuilderAction.h"

#include "../../../../../director/builderDirector.h"
#include "../../../../../node/node/node.h"
#include "../../../../../node/nodeRunInfo/nodeRunInfo.h"
#include "../../../../../win/mainWindow.h"
void RunToTargetNodeBuilderAction::releaTarget( Node *release_target, const SrackInfo &srack_info ) {
	if( release_target == targetNode )
		targetNode = nullptr;
	disconnect( release_target, &Node::release_node_signal, this, &RunToTargetNodeBuilderAction::releaTarget );
	this->trigger( );
}
void RunToTargetNodeBuilderAction::createNodeRunInfoAction( ) {
	NodeRunInfo *nodeRunInfo = builderDirector->getNodeRunInfo( );
	// 1.如果功能编译状态是失效，那么重置它的效果为失效
	// 2.如果目标不存在编译链当中，那么重置它的效果为失效
	if( nodeRunInfo == nullptr || nodeRunInfo->hasBuilderNode( targetNode ) == false ) {
		setEnabled( false );
		return;
	}
	thisEnblen = true;
	setText( tr( "运行到[%1]" ).arg( targetNode->toQString( ) ) );
}
void RunToTargetNodeBuilderAction::releaseNodeRunInfoAction( ) {
	setEnabled( false );
	thisEnblen = false;
	setText( tr( "未匹配节点" ) );
}
void RunToTargetNodeBuilderAction::enabledChanged_Slot( bool change_enbled_flag ) {
	if( change_enbled_flag == false && targetNode == nullptr ) {
		thisEnblen = false;
		targetNode = nullptr;
		setText( tr( "未匹配节点" ) );
		return; // 功能失效，我不管
	}
	createNodeRunInfoAction( );
}
bool RunToTargetNodeBuilderAction::init( ApplicationMenuStack *application_menu_stack ) {
	if( NormalApplicationAction::init( application_menu_stack ) == false )
		return false;
	targetNode = nullptr;
	setText( tr( "未匹配节点" ) );
	setObjectName( tr( "运行到指定节点的功能动作" ) );
	thisEnblen = false;
	setEnabled( false );
	connect( this, &QAction::enabledChanged, this, &RunToTargetNodeBuilderAction::enabledChanged_Slot );
	connect( builderDirector, &BuilderDirector::release_node_run_info_signal, this, &RunToTargetNodeBuilderAction::createNodeRunInfoAction );
	connect( builderDirector, &BuilderDirector::create_node_run_info_signalr, this, &RunToTargetNodeBuilderAction::createNodeRunInfoAction );
	return true;
}
bool RunToTargetNodeBuilderAction::run( MainWindow *parent ) {
	return builderDirector->runToTargetNode( targetNode );
}
void RunToTargetNodeBuilderAction::setTargetNode( Node *target_node ) {
	if( targetNode ) // 取消旧的信号
		disconnect( targetNode, &Node::release_node_signal, this, &RunToTargetNodeBuilderAction::releaTarget );
	targetNode = target_node;
	if( targetNode )
		connect( targetNode, &Node::release_node_signal, this, &RunToTargetNodeBuilderAction::releaTarget );
	if( isEnabled( ) == false )
		setEnabled( true );
	else
		createNodeRunInfoAction( );
}
