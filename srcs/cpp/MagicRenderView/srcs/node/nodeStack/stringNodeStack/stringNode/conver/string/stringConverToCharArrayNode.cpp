#include "stringConverToCharArrayNode.h"

#include <director/varDirector.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "../../../../../port/inputPort/unity/stringInputPort.h"
#include "../../../../../port/outputPort/array/charVectorOutputPort.h"

Def_Entity_NodeTypeName_Function( StringConverToCharArrayNode, Node::tr( "转换/序列/字符串到字符序列" ) );

StringConverToCharArrayNode::StringConverToCharArrayNode( const QString &node_name ) : ProcessNode( node_name ) { outVarPtr = nullptr; }
bool StringConverToCharArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeToolsPtr->appendInputPortType( this, tr( "值" ), stringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "字符" ), charVectorOutputPortPtr, outVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringConverToCharArrayNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool StringConverToCharArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outVarPtr->clear( );
	auto outputPortsPtr = nodeToolsPtr->getRefPort( stringInputPortPtr );
	size_t count = outputPortsPtr->size( );
	if( count == 0 )
		return true;
	auto outputPortArrayPtr = outputPortsPtr->data( );
	OutputPort *outputPortPtr = outputPortArrayPtr[ 0 ];
	auto parentNodePtr = outputPortPtr->getParentNode( );
	auto varDirectorPtr = parentNodePtr->getVarDirector( );
	auto varPtr = outputPortPtr->getVarPtr( );

	QString *stringPtr;
	if( varDirectorPtr->cast_ptr( varPtr, stringPtr ) == false )
		return true;
	auto stringData = stringPtr->data( );
	qsizetype stringLength = stringPtr->length( );
	outVarPtr->resize( stringLength );
	auto data = outVarPtr->data( );
	qsizetype index = 0;
	for( ; index < stringLength; ++index )
		data[ index ] = stringData[ index ];
	return true;
}
