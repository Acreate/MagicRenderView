#include "splitDataTimeNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/dateTimeInputPort.h>
#include <node/port/outputPort/unity/dateOutputPort.h>
#include <node/port/outputPort/unity/timeOutputPort.h>
#include <tools/infoTool.h>

#include "../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( SplitDataTimeNode, Node::tr( "日期时间/切分日期与时间" ) );

SplitDataTimeNode::SplitDataTimeNode( const QString &node_name ) : ProcessNode( node_name ) {
	outDatePtr = nullptr;
	outTimePtr = nullptr;
}
bool SplitDataTimeNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "日期时间" ), dateTimeInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "日期" ), dateOutputPortPtr, outDatePtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "时间" ), timeOutputPortPtr, outTimePtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool SplitDataTimeNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool SplitDataTimeNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	QDateTime *converDateTimePtr;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( dateTimeInputPortPtr, converDateTimePtr ) == false )
		return true;
	*outDatePtr = converDateTimePtr->date( );
	*outTimePtr = converDateTimePtr->time( );
	return true;
}
