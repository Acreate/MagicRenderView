#include "nodeTools.h"

#include "../node/node.h"
#include "../port/inputPort/dynamicTypeInputPort.h"
#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/dynamicTypeOutputPort.h"
#include "../port/outputPort/outputPort.h"

std::vector< InputPort * > * NodeTools::getRefPort( OutputPort *output_port ) {
	if( output_port == nullptr )
		return nullptr;
	return &( output_port->refInputPortVector );
}
const std::vector< InputPort * > * NodeTools::getRefPort( const OutputPort *output_port ) const {
	if( output_port == nullptr )
		return nullptr;
	return &( output_port->refInputPortVector );
}
const std::vector< OutputPort * > * NodeTools::getRefPort( const InputPort *input_port ) {
	if( input_port == nullptr )
		return nullptr;
	return &( input_port->refOutputPortVector );
}
bool NodeTools::getRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector ) {
	size_t refInputPortCount;
	InputPort *const*refInputPortArray;
	size_t refInputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( output_port );
	refInputPortCount = ref->size( );
	if( refInputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refInputPortCount );
	refInputPortArray = ref->data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refInputPortIndex = 0;
	for( ; refInputPortIndex < refInputPortCount; refInputPortIndex += 1 )
		if( refInputPortArray[ refInputPortIndex ] == nullptr )
			continue;
		else {
			current = refInputPortArray[ refInputPortIndex ]->parentNode;
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}
bool NodeTools::getRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector ) {
	size_t refOutputPortCount;
	OutputPort *const*refOutputPortArray;
	size_t refOutputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( input_port );
	refOutputPortCount = ref->size( );
	if( refOutputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refOutputPortCount );
	refOutputPortArray = ref->data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refOutputPortIndex = 0;
	for( ; refOutputPortIndex < refOutputPortCount; refOutputPortIndex += 1 )
		if( refOutputPortArray[ refOutputPortIndex ] == nullptr )
			continue;
		else {
			current = refOutputPortArray[ refOutputPortIndex ]->parentNode;
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}

bool NodeTools::getFilterRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type ) {
	size_t refInputPortCount;
	InputPort *const*refInputPortArray;
	size_t refInputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( output_port );
	refInputPortCount = ref->size( );
	if( refInputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refInputPortCount );
	refInputPortArray = ref->data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refInputPortIndex = 0;
	for( ; refInputPortIndex < refInputPortCount; refInputPortIndex += 1 )
		if( refInputPortArray[ refInputPortIndex ] == nullptr )
			continue;
		else if( current = refInputPortArray[ refInputPortIndex ]->getParentNode( ), current->getNodeType( ) == node_type ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}
bool NodeTools::getFilterNotRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type ) {
	size_t refInputPortCount;
	InputPort *const*refInputPortArray;
	size_t refInputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( output_port );
	refInputPortCount = ref->size( );
	if( refInputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refInputPortCount );
	refInputPortArray = ref->data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refInputPortIndex = 0;
	for( ; refInputPortIndex < refInputPortCount; refInputPortIndex += 1 )
		if( refInputPortArray[ refInputPortIndex ] == nullptr )
			continue;
		else if( current = refInputPortArray[ refInputPortIndex ]->getParentNode( ), current->getNodeType( ) != node_type ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}
bool NodeTools::setPortVar( OutputPort *output_port, void *new_par ) {
	if( output_port == nullptr )
		return false;
	output_port->varPtr = new_par;
	return true;
}
bool NodeTools::setPortVar( DynamicTypeOutputPort *output_port, void *new_par ) {
	if( output_port == nullptr )
		return false;
	output_port->varPtr = new_par;
	return true;
}
bool NodeTools::setPortMultiple( OutputPort *output_port, bool multiple ) {
	if( output_port == nullptr )
		return false;
	output_port->multiple = multiple;
	return true;
}
bool NodeTools::getVarDirector( OutputPort *output_port, VarDirector *&result_var_director, void *&result_var_ptr ) {
	if( output_port == nullptr )
		return false;
	result_var_director = output_port->getVarDirector( );
	if( result_var_director == nullptr )
		return false;
	result_var_ptr = output_port->varPtr;
	return true;
}
bool NodeTools::setVarDirector( OutputPort *output_port, VarDirector *var_director ) {
	if( output_port == nullptr )
		return false;
	output_port->varDirectorPtr = var_director;
	return true;
}
bool NodeTools::setVarDirector( InputPort *input_port, VarDirector *var_director ) {
	if( input_port == nullptr )
		return false;
	input_port->inputPortVarDirectorPtr = var_director;
	return true;
}
bool NodeTools::getInfo( OutputPort *output_port, Node *&result_input_port_node_parent, VarDirector *&result_var_director, void *&result_var_ptr ) {
	if( output_port == nullptr )
		return false;
	result_input_port_node_parent = output_port->parentNode;
	if( result_input_port_node_parent == nullptr )
		return false;
	result_var_director = result_input_port_node_parent->varDirector;
	result_var_ptr = output_port->varPtr;
	return true;
}
bool NodeTools::setInfo( OutputPort *output_port, VarDirector *var_director, void *var_ptr ) {
	if( output_port )
		return false;
	output_port->varDirectorPtr = var_director;
	output_port->varPtr = var_ptr;
	return true;
}
std::vector< OutputPort * > * NodeTools::getRefPort( InputPort *input_port ) {
	if( input_port )
		return nullptr;
	return &input_port->refOutputPortVector;
}
bool NodeTools::setInfo( InputPort *input_port, VarDirector *var_director, void *var_ptr ) {
	if( input_port )
		return false;
	input_port->inputPortVarDirectorPtr = var_director;
	input_port->inputPortVarPtr = var_ptr;
	return true;
}
bool NodeTools::getVarDirector( InputPort *input_port, VarDirector *&result_var_director, void *&result_var_ptr ) {
	if( input_port == nullptr )
		return false;
	result_var_director = input_port->getVarDirector( );
	if( result_var_director == nullptr )
		return false;
	result_var_ptr = input_port->inputPortVarPtr;
	return true;
}
bool NodeTools::getInfo( InputPort *input_port, Node *&result_input_port_node_parent, VarDirector *&result_var_director, void *&result_var_ptr ) {

	if( input_port == nullptr )
		return false;
	result_input_port_node_parent = input_port->parentNode;
	if( result_input_port_node_parent == nullptr )
		return false;
	result_var_director = result_input_port_node_parent->varDirector;
	result_var_ptr = input_port->inputPortVarPtr;
	return true;
}
bool NodeTools::setPortMultiple( InputPort *input_port, bool multiple ) {
	if( input_port == nullptr )
		return false;
	input_port->multiple = multiple;
	return true;
}
bool NodeTools::setPortVar( InputPort *input_port, void *new_par ) {
	if( input_port == nullptr )
		return false;
	input_port->inputPortVarPtr = new_par;
	return true;
}
bool NodeTools::setPortVar( DynamicTypeInputPort *input_port, void *new_par ) {
	if( input_port == nullptr )
		return false;
	input_port->inputPortVarPtr = new_par;
	return true;
}
bool NodeTools::getFilterRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type ) {
	size_t refOutputPortCount;
	OutputPort *const*refOutputPortArray;
	size_t refOutputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( input_port );
	refOutputPortCount = ref->size( );
	if( refOutputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refOutputPortCount );
	refOutputPortArray = ref->data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refOutputPortIndex = 0;
	for( ; refOutputPortIndex < refOutputPortCount; refOutputPortIndex += 1 )
		if( refOutputPortArray[ refOutputPortIndex ] == nullptr )
			continue;
		else if( current = refOutputPortArray[ refOutputPortIndex ]->getParentNode( ), current->getNodeType( ) == node_type ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}
bool NodeTools::getFilterNotRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type ) {
	size_t refOutputPortCount;
	OutputPort *const*refOutputPortArray;
	size_t refOutputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( input_port );
	refOutputPortCount = ref->size( );
	if( refOutputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refOutputPortCount );
	refOutputPortArray = ref->data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refOutputPortIndex = 0;
	for( ; refOutputPortIndex < refOutputPortCount; refOutputPortIndex += 1 )
		if( refOutputPortArray[ refOutputPortIndex ] == nullptr )
			continue;
		else if( current = refOutputPortArray[ refOutputPortIndex ]->getParentNode( ), current->getNodeType( ) != node_type ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}
