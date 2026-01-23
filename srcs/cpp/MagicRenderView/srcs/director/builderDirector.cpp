#include "builderDirector.h"

#include <app/application.h>
#include <director/nodeDirector.h>
#include <node/nodeRunInfo/nodeRunInfo.h>
#include <srack/srackInfo.h>

#include "../menu/app/imp/action/builder/builderPorjectAction.h"
#include "../menu/app/imp/action/builder/nextStepBuilderAction.h"
#include "../menu/app/imp/action/builder/resetBuilderStartNodeProjectAction.h"
#include "../menu/app/imp/action/builder/runBuilderAction.h"
#include "../menu/app/imp/action/builder/runToNextFrmeBuilderAction.h"
#include "../menu/app/imp/action/builder/runToTargetNodeBuilderAction.h"
#include "../menu/app/imp/action/builder/stopBuilderAction.h"
#include "../menu/app/imp/menu/builderApplicationMenu.h"
#include "../menu/app/imp/toolBar/builderApplicationToolBar.h"
void BuilderDirector::updateBuilderActionObjInfo( ) {
	if( nodeRunInfo == nullptr )
		resetBuilderActionObjInfo( );
	else
		validBuilderActionObjInfo( );
}
void BuilderDirector::setRunNodeStatusBuilderMenuActionObjInfo( BuilderApplicationMenu::BuilderApplicationMenuActionList &builder_app_menu_action_list ) {
	builder_app_menu_action_list.builderPorjectAction->setEnabled( false );
	builder_app_menu_action_list.resetBuilderStartNode->setEnabled( false );
	builder_app_menu_action_list.nextStepBuilderAction->setEnabled( false );
	builder_app_menu_action_list.runBuilderAction->setEnabled( false );
	builder_app_menu_action_list.stopBuilderAction->setEnabled( true );
	builder_app_menu_action_list.runToNextFrmeBuilderAction->setEnabled( false );
	builder_app_menu_action_list.runToTargetNodeBuilderAction->setEnabled( false );
}
void BuilderDirector::setRunNodeStatusBuilderToolBarActionObjInfo( BuilderApplicationToolBar::BuilderApplicationToolBarActionList &builder_app_tool_bar_action_list ) {
	builder_app_tool_bar_action_list.builderPorjectAction->setEnabled( false );
	builder_app_tool_bar_action_list.resetBuilderStartNode->setEnabled( false );
	builder_app_tool_bar_action_list.nextStepBuilderAction->setEnabled( false );
	builder_app_tool_bar_action_list.runBuilderAction->setEnabled( false );
	builder_app_tool_bar_action_list.stopBuilderAction->setEnabled( true );
	builder_app_tool_bar_action_list.runToNextFrmeBuilderAction->setEnabled( false );
	builder_app_tool_bar_action_list.runToTargetNodeBuilderAction->setEnabled( false );
}
void BuilderDirector::setRunNodeStatusAction( ) {
	size_t count;
	size_t index;
	BuilderApplicationMenu **menuArrayPtr;
	BuilderApplicationToolBar **toolBarArrayPtr;
	count = menus.size( );
	if( count )
		for( index = 0, menuArrayPtr = menus.data( ); index < count; ++index ) setRunNodeStatusBuilderMenuActionObjInfo( menuArrayPtr[ index ]->normalMenuAction );
	count = toolBars.size( );
	if( count )
		for( index = 0, toolBarArrayPtr = toolBars.data( ); index < count; ++index ) setRunNodeStatusBuilderToolBarActionObjInfo( toolBarArrayPtr[ index ]->normalToolBarAction );
}

void BuilderDirector::resetBuilderMenuActionObjInfo( BuilderApplicationMenu::BuilderApplicationMenuActionList &builder_app_menu_action_list ) {
	builder_app_menu_action_list.builderPorjectAction->setEnabled( true );
	builder_app_menu_action_list.resetBuilderStartNode->setEnabled( false );
	builder_app_menu_action_list.nextStepBuilderAction->setEnabled( false );
	builder_app_menu_action_list.runBuilderAction->setEnabled( false );
	builder_app_menu_action_list.stopBuilderAction->setEnabled( false );
	builder_app_menu_action_list.runToNextFrmeBuilderAction->setEnabled( false );
	builder_app_menu_action_list.runToTargetNodeBuilderAction->setEnabled( false );
}

void BuilderDirector::resetBuilderToolBarActionObjInfo( BuilderApplicationToolBar::BuilderApplicationToolBarActionList &builder_app_tool_bar_action_list ) {
	builder_app_tool_bar_action_list.builderPorjectAction->setEnabled( true );
	builder_app_tool_bar_action_list.resetBuilderStartNode->setEnabled( false );
	builder_app_tool_bar_action_list.nextStepBuilderAction->setEnabled( false );
	builder_app_tool_bar_action_list.runBuilderAction->setEnabled( false );
	builder_app_tool_bar_action_list.stopBuilderAction->setEnabled( false );
	builder_app_tool_bar_action_list.runToNextFrmeBuilderAction->setEnabled( false );
	builder_app_tool_bar_action_list.runToTargetNodeBuilderAction->setEnabled( false );
}

void BuilderDirector::resetBuilderActionObjInfo( ) {
	size_t count;
	size_t index;
	BuilderApplicationMenu **menuArrayPtr;
	BuilderApplicationToolBar **toolBarArrayPtr;
	count = menus.size( );
	if( count )
		for( index = 0, menuArrayPtr = menus.data( ); index < count; ++index ) resetBuilderMenuActionObjInfo( menuArrayPtr[ index ]->normalMenuAction );
	count = toolBars.size( );
	if( count )
		for( index = 0, toolBarArrayPtr = toolBars.data( ); index < count; ++index ) resetBuilderToolBarActionObjInfo( toolBarArrayPtr[ index ]->normalToolBarAction );

	emit release_node_run_info_signal( this, nodeRunInfo );
	delete nodeRunInfo;
	nodeRunInfo = nullptr;
}

void BuilderDirector::validBuilderMenuActionObjInfo( BuilderApplicationMenu::BuilderApplicationMenuActionList &builder_app_menu_action_list ) {
	builder_app_menu_action_list.builderPorjectAction->setEnabled( true );
	builder_app_menu_action_list.resetBuilderStartNode->setEnabled( true );
	builder_app_menu_action_list.nextStepBuilderAction->setEnabled( true );
	builder_app_menu_action_list.runBuilderAction->setEnabled( true );
	builder_app_menu_action_list.stopBuilderAction->setEnabled( true );
	builder_app_menu_action_list.runToNextFrmeBuilderAction->setEnabled( true );
	builder_app_menu_action_list.runToTargetNodeBuilderAction->setEnabled( true );
}
void BuilderDirector::validBuilderToolBarActionObjInfo( BuilderApplicationToolBar::BuilderApplicationToolBarActionList &builder_app_tool_bar_action_list ) {
	builder_app_tool_bar_action_list.builderPorjectAction->setEnabled( true );
	builder_app_tool_bar_action_list.resetBuilderStartNode->setEnabled( true );
	builder_app_tool_bar_action_list.nextStepBuilderAction->setEnabled( true );
	builder_app_tool_bar_action_list.runBuilderAction->setEnabled( true );
	builder_app_tool_bar_action_list.stopBuilderAction->setEnabled( true );
	builder_app_tool_bar_action_list.runToNextFrmeBuilderAction->setEnabled( true );
	builder_app_tool_bar_action_list.runToTargetNodeBuilderAction->setEnabled( true );
}

void BuilderDirector::validBuilderActionObjInfo( ) {
	size_t count;
	size_t index;
	BuilderApplicationMenu **menuArrayPtr;
	BuilderApplicationToolBar **toolBarArrayPtr;
	count = menus.size( );
	if( count )
		for( index = 0, menuArrayPtr = menus.data( ); index < count; ++index )validBuilderMenuActionObjInfo( menuArrayPtr[ index ]->normalMenuAction );
	count = toolBars.size( );
	if( count )
		for( index = 0, toolBarArrayPtr = toolBars.data( ); index < count; ++index )
			validBuilderToolBarActionObjInfo( toolBarArrayPtr[ index ]->normalToolBarAction );
}
void BuilderDirector::removeMenu( NormalApplicationMenu *remove_target ) {
	size_t count;
	size_t index;
	BuilderApplicationMenu **menuArrayPtr;
	count = menus.size( );
	if( count )
		for( index = 0, menuArrayPtr = menus.data( ); index < count; ++index )
			if( menuArrayPtr[ index ] == remove_target ) {
				menus.erase( menus.begin( ) + index );
				return;
			}
}
void BuilderDirector::removeToolBar( NormalApplicationToolBar *remove_target ) {
	size_t count;
	size_t index;
	BuilderApplicationToolBar **toolBarArrayPtr;
	count = toolBars.size( );
	if( count )
		for( index = 0, toolBarArrayPtr = toolBars.data( ); index < count; ++index )
			if( toolBarArrayPtr[ index ] == remove_target ) {
				toolBars.erase( toolBars.begin( ) + index );
				return;
			}
}
void BuilderDirector::autoRunStatusChange_Slot( NodeRunInfo *change_obj, bool new_status ) {
	if( change_obj != nodeRunInfo )
		return;
	if( new_status )
		updateBuilderActionObjInfo( );
	else
		setRunNodeStatusAction( );
}
BuilderDirector::BuilderDirector( ) {
	nodeRunInfo = nullptr;
}
BuilderDirector::~BuilderDirector( ) {
	if( nodeRunInfo ) {
		emit release_node_run_info_signal( this, nodeRunInfo );
		delete nodeRunInfo;
		nodeRunInfo = nullptr;
	}
	updateBuilderActionObjInfo( );
}
bool BuilderDirector::init( ) {
	disconnect( );
	instancePtr = Application::getInstancePtr( );
	mainWindow = instancePtr->getMainWindow( );
	nodeDirector = instancePtr->getNodeDirector( );
	if( nodeRunInfo ) {
		emit release_node_run_info_signal( this, nodeRunInfo );
		delete nodeRunInfo;
	}
	nodeRunInfo = nullptr;
	connect( nodeDirector, &NodeDirector::finish_create_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::dis_connect_ref_output_port_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::connect_ref_output_port_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::dis_connect_ref_input_port_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::connect_ref_input_port_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::connect_ref_input_port_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::release_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	return true;
}
bool BuilderDirector::addMenu( BuilderApplicationMenu *builder_application_menu ) {

	menus.emplace_back( builder_application_menu );
	connect( builder_application_menu, &NormalApplicationMenu::release_signal, this, &BuilderDirector::removeMenu );
	updateBuilderActionObjInfo( );
	return true;
}
bool BuilderDirector::addToolBar( BuilderApplicationToolBar *builder_application_tool_bar ) {
	toolBars.emplace_back( builder_application_tool_bar );
	connect( builder_application_tool_bar, &NormalApplicationToolBar::release_signal, this, &BuilderDirector::removeToolBar );
	updateBuilderActionObjInfo( );
	return true;
}
bool BuilderDirector::runToNextFrame( ) {
	if( nodeRunInfo == nullptr )
		return false;
	return nodeRunInfo->runToNextFrame( );
}
bool BuilderDirector::runToTargetNode( const Node *target_node_ptr ) {
	if( nodeRunInfo == nullptr )
		return false;
	bool runToNode = nodeRunInfo->runToNode( target_node_ptr );
	updateBuilderActionObjInfo( );
	return runToNode;
}
bool BuilderDirector::builderNodeProject( ) {
	if( nodeRunInfo ) {
		emit release_node_run_info_signal( this, nodeRunInfo );
		delete nodeRunInfo;
	}
	nodeRunInfo = nodeDirector->builderCurrentAllNodeAtNodeRunInfo( );
	updateBuilderActionObjInfo( );
	if( nodeRunInfo == nullptr )
		return false;
	emit create_node_run_info_signalr( this, nodeRunInfo );
	connect( nodeRunInfo, &NodeRunInfo::auto_run_status_change_signal, this, &BuilderDirector::
			autoRunStatusChange_Slot );
	return true;
}
bool BuilderDirector::resetStartNodeProject( ) {
	if( nodeRunInfo == nullptr )
		return false;
	return nodeRunInfo->resetRunStartNode( );
}
bool BuilderDirector::nextStepBuilderNode( ) {
	if( nodeRunInfo == nullptr )
		return false;
	return nodeRunInfo->runNextNode( );
}
bool BuilderDirector::runBuilderBuilderNode( ) {
	if( nodeRunInfo == nullptr )
		return false;
	return nodeRunInfo->runResidueNode( );
}
bool BuilderDirector::stopBuilderBuilderNode( ) {
	if( nodeRunInfo == nullptr )
		return false;
	return nodeRunInfo->runStopNode( );
}
