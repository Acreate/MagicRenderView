#include "debugInfoNode.h"

#include <app/application.h>
#include <director/printerDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../director/nodeDirector.h"
#include "../../../../../director/nodeInfoEditorDirector.h"
#include "../../../../../tools/varDirectorTools.h"
#include "../../../../nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h"
#include "../../../../nodeTools/nodeTools.h"
#include "../../editorNodeInfoWidgets/debugNodeInfoWidget/debugNodeInfoWidget.h"

Def_Entity_NodeTypeName_Function( DebugInfoNode, Node::tr( "输出/值" ) );

bool DebugInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "输出" ), inputBugPort ) == false )
			return false;
		nodeToolsPtr->setPortMultiple( inputBugPort, true );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool DebugInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool DebugInfoNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto debugInfoWidget = qobject_cast< DebugNodeInfoWidget * >( release_ptr );
	if( debugInfoWidget == nullptr )
		return false;
	debugNodeInfoWidget = debugInfoWidget;
	return true;
}
void DebugInfoNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( debugNodeInfoWidget != release_ptr )
		return;
	debugNodeInfoWidget = nullptr;
}

NodeInfoWidget * DebugInfoNode::getNodeEditorWidget( ) {
	if( debugNodeInfoWidget )
		return debugNodeInfoWidget;
	return new DebugNodeInfoWidget( this );
}

bool DebugInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	NodeInfoWidget *resultNodeInfoEditorWidget;
	if( instancePtr->getNodeInfoEditorDirector( )->getNodeInfoEditorWidget( this, resultNodeInfoEditorWidget ) == false )
		return true;
	if( debugNodeInfoWidget != resultNodeInfoEditorWidget ) {
		resultNodeInfoEditorWidget->hide( );
		return true;
	}
	if( debugNodeInfoWidget->initNodeInfo( this ) == false ) {
		debugNodeInfoWidget->hide( );
		return true;
	}
	debugNodeInfoWidget->show( );

	auto outputPorts = nodeToolsPtr->getRefPort( inputBugPort );
	size_t count = outputPorts->size( );
	size_t index = 0;
	OutputPort **outputPortArrayPtr;
	VarDirector *varDirectorPtr;
	Node *parentNodePtr;
	void *varPtr;
	QString resultString;
	Application *instance;
	PrinterDirector *printerDirectorPtr;
	if( count ) {
		instance = Application::getInstancePtr( );
		printerDirectorPtr = instance->getPrinterDirector( );
		outputPortArrayPtr = outputPorts->data( );
		for( ; index < count; ++index ) {
			parentNodePtr = outputPortArrayPtr[ index ]->getParentNode( );
			if( parentNodePtr ) {
				varDirectorPtr = parentNodePtr->getVarDirector( );
				varPtr = outputPortArrayPtr[ index ]->getVarPtr( );
				if( VarDirectorTools::toString( varDirectorPtr, varPtr, resultString ) ) {
					debugNodeInfoWidget->appendPortInfoMsg( outputPortArrayPtr[ index ], resultString );
					continue;
				}
				printerDirectorPtr->info( tr( "[%1/%2] 端口异常" ).arg( parentNodePtr->getNodeTitleName( ) ).arg( outputPortArrayPtr[ index ]->getPortName( ) ), Create_SrackInfo( ) );
				continue;
			}
			printerDirectorPtr->info( tr( "[%1] 端口异常" ).arg( outputPortArrayPtr[ index ]->getPortName( ) ), Create_SrackInfo( ) );
		}
	}
	return true;
}
