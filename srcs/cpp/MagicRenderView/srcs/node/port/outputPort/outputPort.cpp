#include "outputPort.h"

#include "../../../director/varDirector.h"

#include "../inputPort/inputPort.h"
OutputPort::OutputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QObject *parent ) : QObject( parent ), instancePtr( instance_ptr ), varDirector( var_director ), name( name ), node( node ) { }
OutputPort::~OutputPort( ) {
	emit release_node_signal( this );
}
bool OutputPort::link( InputPort *input_port_obj_port ) {
	size_t count = linkThisInputPortVector.size( );
	auto linkThisOutputPortArrayPtr = linkThisInputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( linkThisOutputPortArrayPtr[ index ] == input_port_obj_port )
			return true;
	QString outputPortTypeName;
	if( varDirector->getObjPtrAtTypeName( input_port_obj_port->getVarPtr( ), outputPortTypeName ) == false )
		return false;
	if( outputPortTypeName != varTypeName )
		return false;
	linkThisInputPortVector.emplace_back( input_port_obj_port );
	connect( input_port_obj_port, &InputPort::release_node_signal, this, &OutputPort::unlink );
	emit create_link_signal( this, input_port_obj_port );
	input_port_obj_port->link( this );
	return true;
}
bool OutputPort::unlink( InputPort *input_port_obj_port ) {
	size_t count = linkThisInputPortVector.size( );
	auto linkThisOutputPortArrayPtr = linkThisInputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( linkThisOutputPortArrayPtr[ index ] == input_port_obj_port )
			break;
	if( index == count )
		return false;
	linkThisInputPortVector.erase( linkThisInputPortVector.begin( ) + index );
	disconnect( input_port_obj_port, &InputPort::release_node_signal, this, &OutputPort::unlink );
	emit release_link_signal( this, input_port_obj_port );
	input_port_obj_port->unlink( this );
	return true;
}
bool OutputPort::refInputPortHasNode( Node *input_port_node ) {
	size_t count = linkThisInputPortVector.size( );
	auto outputPortArrayPtr = linkThisInputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ]->node == input_port_node )
			return true;
	return false;
}
bool OutputPort::refInputPortHasPort( InputPort *input_port ) {
	size_t count = linkThisInputPortVector.size( );
	auto outputPortArrayPtr = linkThisInputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ] == input_port )
			return true;
	return false;
}
