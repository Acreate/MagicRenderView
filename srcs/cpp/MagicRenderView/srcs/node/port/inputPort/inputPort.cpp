#include "inputPort.h"

#include "../../../app/application.h"

#include "../../../director/varDirector.h"

#include "../../../tools/vectorTools.h"

#include "../outputPort/outputPort.h"

InputPort::InputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QWidget *parent ) : QWidget( parent ), instancePtr( instance_ptr ), varDirector( var_director ), name( name ), node( node ) { }
bool InputPort::refOutputPortHasNode( Node *output_port_node ) {
	size_t count = linkThisOutputPortVector.size( );
	auto outputPortArrayPtr = linkThisOutputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ]->node == output_port_node )
			return true;
	return false;
}
bool InputPort::refOutputPortHasPort( OutputPort *output_port ) {
	size_t count = linkThisOutputPortVector.size( );
	auto outputPortArrayPtr = linkThisOutputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ] == output_port )
			return true;
	return false;
}

bool InputPort::link( OutputPort *output_port_obj_port ) {
	if( output_port_obj_port->varTypeName != varTypeName )
		return false;
	size_t index = 0;
	size_t count = linkThisOutputPortVector.size( );
	auto linkThisOutputPortArrayPtr = linkThisOutputPortVector.data( );
	for( ; index < count; ++index )
		if( linkThisOutputPortArrayPtr[ index ] == output_port_obj_port || linkThisOutputPortArrayPtr[ index ] == nullptr )
			break;

	if( linkThisOutputPortArrayPtr[ index ] == output_port_obj_port )
		return true; // 已经存在 output_port_obj_port 元素

	if( index == count )// 序列末尾，则追加
		linkThisOutputPortVector.emplace_back( output_port_obj_port );
	else // linkThisOutputPortArrayPtr[ index ] == nullptr 则赋值
		linkThisOutputPortArrayPtr[ index ] = output_port_obj_port;
	connect( output_port_obj_port, &OutputPort::release_node_signal, this, &InputPort::unlink );
	emit create_link_signal( this, output_port_obj_port );
	return true;
}
bool InputPort::unlink( OutputPort *output_port_obj_port ) {
	size_t count = linkThisOutputPortVector.size( );
	auto linkThisOutputPortArrayPtr = linkThisOutputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( linkThisOutputPortArrayPtr[ index ] == output_port_obj_port || linkThisOutputPortArrayPtr[ index ] == nullptr )
			break;
	if( index == count )
		return false; // 不存在链接
	linkThisOutputPortArrayPtr[ index ] = nullptr;
	count -= 1;
	for( ; index < count; ++index )
		if( linkThisOutputPortArrayPtr[ index ] == nullptr )
			break;// 遭遇第一个 nullptr,则退出
		else // 后面一个元素，覆盖前面一个元素
			linkThisOutputPortArrayPtr[ index ] = linkThisOutputPortArrayPtr[ index + 1 ];
	linkThisOutputPortArrayPtr[ index ] = nullptr; // 最后一个元素覆盖为 0

	disconnect( output_port_obj_port, &OutputPort::release_node_signal, this, &InputPort::unlink );
	emit release_link_signal( this, output_port_obj_port );
	return true;
}
InputPort::~InputPort( ) {
	emit release_node_signal( this );
}
