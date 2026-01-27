#include "binCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/binOutputPort.h>

#include "binCreateNodeEditorWidget/unity/binCreateUnityNodeEditorWidget.h"

Def_Entity_NodeTypeName_Function( BinCreateUnityNode, Node::tr("创建/单元/二进制" ) );

BinCreateUnityNode::BinCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
	editorWidget = nullptr;
}
bool BinCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool BinCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool BinCreateUnityNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto nodeEditorWidget = qobject_cast< decltype(editorWidget) >( release_ptr );
	if( nodeEditorWidget == nullptr )
		return false;
	editorWidget = nodeEditorWidget;
	return true;
}
void BinCreateUnityNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( release_ptr != editorWidget )
		return;
	editorWidget = nullptr;
}
NodeInfoWidget * BinCreateUnityNode::getNodeInfoWidget( ) {
	if( editorWidget )
		return editorWidget;
	return new BinCreateUnityNodeEditorWidget( this, outputVarPtr );
}
bool BinCreateUnityNode::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	uint8_t *uint8Ptr = nullptr;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	if( varDirector.create( uint8Ptr ) == false )
		return false;

	void *converPtr;
	converPtr = uint64Ptr;
	if( varDirector.toVar( result_use_count, source_array_ptr, source_array_count, converPtr ) == false )
		return false;
	auto mod = source_array_count - result_use_count;
	if( *uint64Ptr > mod )
		return false; // 剩余数量少于需求数量
	auto offset = source_array_ptr + result_use_count;
	converPtr = uint8Ptr;
	if( varDirector.toVar( result_use_count, offset, mod, converPtr ) == false )
		return false;
	*outputVarPtr = *uint8Ptr;
	result_use_count = mod - result_use_count;
	return true;
}
bool BinCreateUnityNode::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	uint8_t *uint8Ptr = nullptr;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	if( varDirector.create( uint8Ptr ) == false )
		return false;
	std::vector< uint8_t > buff;
	*uint8Ptr = *outputVarPtr;
	if( varDirector.toVector( uint8Ptr, buff ) == false )
		return false;

	*uint64Ptr = buff.size( );
	if( varDirector.toVector( uint64Ptr, result_vector_data ) == false )
		return false;
	result_vector_data.append_range( buff );
	return true;
}
bool BinCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool BinCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
