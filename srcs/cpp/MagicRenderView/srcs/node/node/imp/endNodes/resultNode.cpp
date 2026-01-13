#include "resultNode.h"

#include "../../../port/inputPort/interface/interFaceInputPort.h"
#include "../../../port/inputPort/toBegin/toBeginInputPort.h"
#include "../../../port/outputPort/outputPort.h"
#include "../../beginNode.h"

bool ResultNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "结束" ), interFaceInputPort );
		Def_AppendInputPortType( tr( "返回" ), toBeginInputPort );
		return true;
	};
	return EndNode::initEx( parent );
}
bool ResultNode::updateLayout( ) {
	if( EndNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ResultNode::readyNodeRunData( ) {
	return true;
}

bool ResultNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	auto beginNode = qobject_cast< BeginNode * >( toBeginInputPort->getParentNode( ) );
	if( beginNode == nullptr )
		return false;
	return updateBeginData( beginNode );
}
bool ResultNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) {
	size_t refOutputPortCount;
	OutputPort **refOutputPortArray;
	size_t refOutputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	BeginNode *beginNode;
	auto ref = getRefPort( toBeginInputPort );
	refOutputPortCount = ref.size( );
	if( refOutputPortCount == 0 )
		return true;

	result_next_run_advise_node_vector.resize( refOutputPortCount );
	refOutputPortArray = ref.data( );
	destArray = result_next_run_advise_node_vector.data( );

	desCount = 0;
	refOutputPortIndex = 0;
	for( ; refOutputPortIndex < refOutputPortCount; refOutputPortIndex += 1 )
		if( refOutputPortArray[ refOutputPortIndex ] == nullptr )
			continue;
		else if( current = refOutputPortArray[ refOutputPortIndex ]->getParentNode( ), current->getNodeType( ) == NodeEnum::NodeType::Begin ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			beginNode = qobject_cast< BeginNode * >( current );
			if( beginNode == nullptr )
				continue;
			if( updateBeginData( beginNode ) == false )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_next_run_advise_node_vector.resize( desCount );
	return true;
}
