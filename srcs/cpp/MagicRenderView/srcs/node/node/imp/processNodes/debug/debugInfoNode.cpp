#include "debugInfoNode.h"

#include <app/application.h>
#include <director/printerDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

bool DebugInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "输出" ), inputBugPort );
		setPortMultiple( inputBugPort, true );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool DebugInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool DebugInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	auto outputPorts = getRefPort( inputBugPort );
	size_t count = outputPorts.size( );
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
		outputPortArrayPtr = outputPorts.data( );
		for( ; index < count; ++index ) {
			parentNodePtr = outputPortArrayPtr[ index ]->getParentNode( );
			if( parentNodePtr ) {
				varDirectorPtr = parentNodePtr->getVarDirector( );
				varPtr = outputPortArrayPtr[ index ]->getVarPtr( );
				if( infoTool::toString( varDirectorPtr, varPtr, resultString ) ) {
					resultString = tr( "[%1/%2]:%3" ).arg( parentNodePtr->getNodeTitleName( ) ).arg( outputPortArrayPtr[ index ]->getPortName( ) ).arg( resultString );
					printerDirectorPtr->info( resultString, Create_SrackInfo( ) );
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
