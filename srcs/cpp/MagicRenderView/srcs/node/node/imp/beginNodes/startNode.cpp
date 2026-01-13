#include "startNode.h"

#include <qdatetime.h>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
#include "../../../../tools/arrayTools.h"
#include "../../../../tools/vectorTools.h"
#include "../../../port/inputPort/inputPort.h"
#include "../../../port/outputPort/begin/beginOutputPort .h"
#include "../../../port/outputPort/toBegin/toBeginOutputPort.h"

StartNode::StartNode( const QString &node_name ) : BeginNode( node_name ) {
	var = nullptr;
}
bool StartNode::initEx( MainWidget *parent ) {

	initExCallFunction = [this] ( MainWidget *main_widget ) {
		Def_AppendBindVarOutputPortType( tr( "开始" ), beginOutputPort, var );
		Def_AppendOutputPortType( tr( "返回" ), toBeginOutputPort );
		return true;
	};

	return BeginNode::initEx( parent );
}

bool StartNode::updateLayout( ) {
	if( BeginNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StartNode::readNextBeginNodeData( ) {
	readUpdate = true;
	return true;
}
bool StartNode::readyNodeRunData( ) {
	readUpdate = true;
	*var = 0;
	readUpdate = false;
	return true;
}
bool StartNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector ) {
	return true;
}
bool StartNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	if( readUpdate == false )
		return true;
	*var += 1;
	readUpdate = false;
	return true;
}
bool StartNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) {
	size_t refInputPortCount;
	InputPort **refInputPortArray;
	size_t refInputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;

	auto ref = getRefPort( beginOutputPort );
	refInputPortCount = ref.size( );
	if( refInputPortCount == 0 )
		return true;

	result_next_run_advise_node_vector.resize( refInputPortCount );
	refInputPortArray = ref.data( );
	destArray = result_next_run_advise_node_vector.data( );

	desCount = 0;
	refInputPortIndex = 0;
	for( ; refInputPortIndex < refInputPortCount; refInputPortIndex += 1 )
		if( refInputPortArray[ refInputPortIndex ] == nullptr )
			continue;
		else if( current = refInputPortArray[ refInputPortIndex ]->getParentNode( ), current->getNodeType( ) != NodeEnum::NodeType::End ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;
		}
	result_next_run_advise_node_vector.resize( desCount );
	return true;
}
