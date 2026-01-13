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
		if( appendInputPortType< >( tr( "日期时间" ), dateTimeInputPortPtr ) == false )
			return false;
		if( appendOutputPortType< >( tr( "日期" ), dateOutputPortPtr ) == false )
			return false;
		if( appendOutputPortType< >( tr( "时间" ), timeOutputPortPtr ) == false )
			return false;
		if( outDatePtr )
			varDirector->release( outDatePtr );
		if( varDirector->create( outDatePtr ) == false )
			return false;
		if( outTimePtr )
			varDirector->release( outTimePtr );
		if( varDirector->create( outTimePtr ) == false )
			return false;
		if( setPortVar( dateOutputPortPtr, outDatePtr ) == false )
			return false;
		if( setPortVar( timeOutputPortPtr, outTimePtr ) == false )
			return false;
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
