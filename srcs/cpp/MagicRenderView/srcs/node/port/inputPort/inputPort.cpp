#include "inputPort.h"

#include "../../../app/application.h"

#include "../../../director/varDirector.h"

#include "../outputPort/outputPort.h"

InputPort::InputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QObject *parent ) : QObject( parent ), instancePtr( instance_ptr ), varDirector( var_director ), name( name ), node( node ) { }
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
	size_t count = linkThisOutputPortVector.size( );
	auto linkThisOutputPortArrayPtr = linkThisOutputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( linkThisOutputPortArrayPtr[ index ] == output_port_obj_port )
			return true;
	QString outputPortTypeName;
	if( varDirector->getObjPtrAtTypeName( output_port_obj_port->getVarPtr( ), outputPortTypeName ) == false )
		return false;
	if( outputPortTypeName != varTypeName )
		return false;
	linkThisOutputPortVector.emplace_back( output_port_obj_port );
	connect( output_port_obj_port, &OutputPort::release_node_signal, this, &InputPort::unlink );
	emit create_link_signal( this, output_port_obj_port );

	output_port_obj_port->link( this );

	return true;
}
bool InputPort::unlink( OutputPort *output_port_obj_port ) {
	size_t count = linkThisOutputPortVector.size( );
	auto linkThisOutputPortArrayPtr = linkThisOutputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( linkThisOutputPortArrayPtr[ index ] == output_port_obj_port )
			break;
	if( index == count )
		return false;
	linkThisOutputPortVector.erase( linkThisOutputPortVector.begin( ) + index );
	disconnect( output_port_obj_port, &OutputPort::release_node_signal, this, &InputPort::unlink );
	emit release_link_signal( this, output_port_obj_port );
	output_port_obj_port->unlink( this );
	return true;
}
InputPort::~InputPort( ) {
	emit release_node_signal( this );
}
