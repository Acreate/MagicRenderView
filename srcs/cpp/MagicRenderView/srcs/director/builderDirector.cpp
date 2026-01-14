#include "builderDirector.h"

#include "../app/application.h"
#include <win/mainWindow.h>

#include "../menu/app/imp/action/builder/builderPorjectAction.h"
#include "../menu/app/imp/action/builder/nextStepBuilderAction.h"
#include "../menu/app/imp/action/builder/resetBuilderStartNodeProjectAction.h"
#include "../menu/app/imp/action/builder/runBuilderAction.h"
#include "../menu/app/imp/action/builder/stopBuilderAction.h"
#include "../menu/app/imp/menu/builderApplicationMenu.h"
#include "../menu/app/imp/toolBar/builderApplicationToolBar.h"
#include "../node/nodeRunInfo/nodeRunInfo.h"
#include "../srack/srackInfo.h"
#include "nodeDirector.h"
#include "printerDirector.h"
void BuilderDirector::updateBuilderActionObjInfo( ) {
	if( nodeRunInfo == nullptr )
		resetBuilderActionObjInfo( );
	else
		validBuilderActionObjInfo( );
}
void BuilderDirector::resetBuilderActionObjInfo( ) {
	size_t count;
	size_t index;
	BuilderApplicationMenu **menuArrayPtr;
	BuilderApplicationToolBar **toolBarArrayPtr;
	count = menus.size( );
	if( count )
		for( index = 0, menuArrayPtr = menus.data( ); index < count; ++index ) {
			auto &normalMenuAction = menuArrayPtr[ index ]->normalMenuAction;
			normalMenuAction.builderPorjectAction->setEnabled( true );
			normalMenuAction.resetBuilderStartNode->setEnabled( false );
			normalMenuAction.nextStepBuilderAction->setEnabled( false );
			normalMenuAction.runBuilderAction->setEnabled( false );
			normalMenuAction.stopBuilderAction->setEnabled( false );
		}
	count = toolBars.size( );
	if( count )
		for( index = 0, toolBarArrayPtr = toolBars.data( ); index < count; ++index ) {
			auto &normalToolBarAction = toolBarArrayPtr[ index ]->normalToolBarAction;
			normalToolBarAction.builderPorjectAction->setEnabled( true );
			normalToolBarAction.resetBuilderStartNode->setEnabled( false );
			normalToolBarAction.nextStepBuilderAction->setEnabled( false );
			normalToolBarAction.runBuilderAction->setEnabled( false );
			normalToolBarAction.stopBuilderAction->setEnabled( false );
		}
}
void BuilderDirector::validBuilderActionObjInfo( ) {
	size_t count;
	size_t index;
	BuilderApplicationMenu **menuArrayPtr;
	BuilderApplicationToolBar **toolBarArrayPtr;
	count = menus.size( );
	if( count )
		for( index = 0, menuArrayPtr = menus.data( ); index < count; ++index ) {
			auto &normalMenuAction = menuArrayPtr[ index ]->normalMenuAction;
			normalMenuAction.builderPorjectAction->setEnabled( true );
			normalMenuAction.resetBuilderStartNode->setEnabled( true );
			normalMenuAction.nextStepBuilderAction->setEnabled( true );
			normalMenuAction.runBuilderAction->setEnabled( true );
			normalMenuAction.stopBuilderAction->setEnabled( true );
		}
	count = toolBars.size( );
	if( count )
		for( index = 0, toolBarArrayPtr = toolBars.data( ); index < count; ++index ) {
			auto &normalToolBarAction = toolBarArrayPtr[ index ]->normalToolBarAction;
			normalToolBarAction.builderPorjectAction->setEnabled( true );
			normalToolBarAction.resetBuilderStartNode->setEnabled( true );
			normalToolBarAction.nextStepBuilderAction->setEnabled( true );
			normalToolBarAction.runBuilderAction->setEnabled( true );
			normalToolBarAction.stopBuilderAction->setEnabled( true );
		}
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
BuilderDirector::~BuilderDirector( ) {
	if( nodeRunInfo ) {
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
	nodeRunInfo = nullptr;
	connect( nodeDirector, &NodeDirector::finish_create_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::dis_connect_ref_output_port_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::connect_ref_output_port_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::dis_connect_ref_input_port_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	connect( nodeDirector, &NodeDirector::connect_ref_input_port_node_signal, this, &BuilderDirector::resetBuilderActionObjInfo );
	return true;
}
bool BuilderDirector::addMenu( BuilderApplicationMenu *builder_application_menu ) {
	builder_application_menu->normalMenuAction.builderPorjectAction->setEnabled( true );
	builder_application_menu->normalMenuAction.resetBuilderStartNode->setEnabled( false );
	builder_application_menu->normalMenuAction.nextStepBuilderAction->setEnabled( false );
	builder_application_menu->normalMenuAction.runBuilderAction->setEnabled( false );
	builder_application_menu->normalMenuAction.stopBuilderAction->setEnabled( false );
	menus.emplace_back( builder_application_menu );
	connect( builder_application_menu, &NormalApplicationMenu::release_signal, this, &BuilderDirector::removeMenu );
	return true;
}
bool BuilderDirector::addToolBar( BuilderApplicationToolBar *builder_application_tool_bar ) {
	builder_application_tool_bar->normalToolBarAction.builderPorjectAction->setEnabled( true );
	builder_application_tool_bar->normalToolBarAction.resetBuilderStartNode->setEnabled( false );
	builder_application_tool_bar->normalToolBarAction.nextStepBuilderAction->setEnabled( false );
	builder_application_tool_bar->normalToolBarAction.runBuilderAction->setEnabled( false );
	builder_application_tool_bar->normalToolBarAction.stopBuilderAction->setEnabled( false );
	toolBars.emplace_back( builder_application_tool_bar );
	connect( builder_application_tool_bar, &NormalApplicationToolBar::release_signal, this, &BuilderDirector::removeToolBar );
	return true;
}
bool BuilderDirector::builderNodeProject( ) {
	if( nodeRunInfo )
		delete nodeRunInfo;
	nodeRunInfo = nodeDirector->builderCurrentAllNodeAtNodeRunInfo( );
	updateBuilderActionObjInfo( );
	if( nodeRunInfo == nullptr )
		return false;
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
