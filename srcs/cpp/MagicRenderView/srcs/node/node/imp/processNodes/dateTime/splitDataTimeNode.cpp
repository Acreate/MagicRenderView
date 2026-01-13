#include "splitDataTimeNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/dateTimeOutputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <tools/infoTool.h>

#include "../../../../port/inputPort/unity/dateTimeInputPort.h"
#include "../../../../port/outputPort/unity/dateOutputPort.h"
#include "../../../../port/outputPort/unity/timeOutputPort.h"

SplitDataTimeNode::SplitDataTimeNode( const QString &node_name ) : ProcessNode( node_name ) {
	outDatePtr = nullptr;
	outTimePtr = nullptr;
}
bool SplitDataTimeNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "日期时间" ), dateTimeInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "日期" ), dateOutputPortPtr, outDatePtr );
		Def_AppendBindVarOutputPortType( tr( "时间" ), timeOutputPortPtr, outTimePtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool SplitDataTimeNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool SplitDataTimeNode::readyNodeRunData( ) {
	return true;
}
bool SplitDataTimeNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	auto outputPorts = getRefPort( dateTimeInputPortPtr );
	size_t count = outputPorts.size( );
	if( count == 0 )
		return true;
	auto outputPort = outputPorts.data( )[ 0 ];
	auto varDirector = outputPort->getVarDirector( );
	if( varDirector == nullptr )
		return true;
	auto varPtr = outputPort->getVarPtr( );
	QDateTime *converDateTimePtr;
	if( varDirector->cast_ptr( varPtr, converDateTimePtr ) == false )
		return true;
	*outDatePtr = converDateTimePtr->date( );
	*outTimePtr = converDateTimePtr->time( );
	return true;
}
