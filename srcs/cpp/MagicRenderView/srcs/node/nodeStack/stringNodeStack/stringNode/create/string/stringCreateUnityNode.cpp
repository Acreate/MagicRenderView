#include "stringCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "stringCreateNodeEditorWidget/unity/stringCreateUnityNodeEditorWidget.h"

Def_Entity_NodeTypeName_Function( StringCreateUnityNode, Node::tr( "创建/单元/字符串" ) );

StringCreateUnityNode::StringCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
	editorWidget = nullptr;
}
bool StringCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringCreateUnityNode::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	void *converPtr = uint64Ptr;
	if( varDirector.toVar( result_use_count, source_array_ptr, source_array_count, converPtr ) == false )
		return false;
	auto mod = source_array_count - result_use_count;
	if( mod < *uint64Ptr )
		return false;
	auto offset = source_array_ptr + result_use_count;
	converPtr = outputVarPtr;
	if( this->varDirector->toVar( result_use_count, offset, mod, converPtr ) == false )
		return false;
	result_use_count = offset + result_use_count - source_array_ptr;
	return true;
}
bool StringCreateUnityNode::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	std::vector< uint8_t > buff;
	if( this->varDirector->toVector( outputVarPtr, buff ) == false )
		return false;
	*uint64Ptr = buff.size( );
	if( varDirector.toVector( uint64Ptr, result_vector_data ) == false )
		return false;
	result_vector_data.append_range( buff );
	return true;
}
bool StringCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool StringCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
bool StringCreateUnityNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto nodeEditorWidget = qobject_cast< decltype(editorWidget) >( release_ptr );
	if( nodeEditorWidget == nullptr )
		return false;
	editorWidget = nodeEditorWidget;
	return true;
}
void StringCreateUnityNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( release_ptr != editorWidget )
		return;
	editorWidget = nullptr;
}
NodeInfoWidget * StringCreateUnityNode::getNodeInfoWidget( ) {
	if( editorWidget )
		return editorWidget;
	return new StringCreateUnityNodeEditorWidget( this, outputVarPtr );
}
