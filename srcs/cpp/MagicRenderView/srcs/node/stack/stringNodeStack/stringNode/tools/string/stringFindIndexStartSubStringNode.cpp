#include "stringFindIndexStartSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "../../../../../port/inputPort/unity/intInputPort.h"
#include "../../../../../port/inputPort/unity/uIntInputPort.h"

StringFindIndexStartSubStringNode::StringFindIndexStartSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringFindIndexStartSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "原始字符串" ), stringInputPortPtr );
		Def_AppendInputPortType( tr( "查找字符串" ), findTargetSubStringInputPortPtr );
		Def_AppendInputPortType( tr( "开始位置" ), findStrtIndexInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "位置" ), outputPort, outputVarPtr );
		*outputVarPtr = -1;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringFindIndexStartSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringFindIndexStartSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringFindIndexStartSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	auto outputPorts = nodeToolsPtr->getRefPort( stringInputPortPtr );
	size_t count = outputPorts->size( );
	if( count == 0 )
		return true;
	auto outputPort = outputPorts->data( )[ 0 ];
	auto varDirector = outputPort->getVarDirector( );
	if( varDirector == nullptr )
		return true;
	auto varPtr = outputPort->getVarPtr( );
	QString *orgString;
	if( varDirector->cast_ptr( varPtr, orgString ) == false )
		return true;

	outputPorts = nodeToolsPtr->getRefPort( findTargetSubStringInputPortPtr );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPort = outputPorts->data( )[ 0 ];
	varDirector = outputPort->getVarDirector( );
	if( varDirector == nullptr )
		return true;
	varPtr = outputPort->getVarPtr( );
	QString *findString;
	if( varDirector->cast_ptr( varPtr, findString ) == false )
		return true;
	*outputVarPtr = orgString->indexOf( *findString );
	return true;
}
