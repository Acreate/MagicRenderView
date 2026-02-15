#include "colorCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "colorCreateNodeEditorWidget/unity/colorCreateUnityNodeEditorWidget.h"

Def_Entity_NodeTypeName_Function( ColorCreateUnityNode, Node::tr( "创建/单元/颜色" ) );

NodeInfoWidget * ColorCreateUnityNode::getNodeInfoWidget( ) {
	if( editorWidget )
		return editorWidget;
	return new ColorCreateUnityNodeEditorWidget( this, outputVarPtr );
}
bool ColorCreateUnityNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto nodeEditorWidget = qobject_cast< decltype(editorWidget) >( release_ptr );
	if( nodeEditorWidget == nullptr )
		return false;
	editorWidget = nodeEditorWidget;
	return true;
}
void ColorCreateUnityNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( release_ptr != editorWidget )
		return;

	editorWidget = nullptr;
}
bool ColorCreateUnityNode::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {
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
bool ColorCreateUnityNode::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
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
ColorCreateUnityNode::ColorCreateUnityNode( const QString &node_name ) : CreateNode( node_name ) {
	outputVarPtr = nullptr;
	editorWidget = nullptr;
}
bool ColorCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = QColor( 0, 0, 0, 255 );
		return true;
	};
	return CreateNode::initEx( parent );
}
bool ColorCreateUnityNode::updateLayout( ) {
	if( CreateNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool ColorCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
