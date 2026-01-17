#include "nodeTools.h"

#include "../../director/varDirector.h"
#include "../../tools/pathTools.h"
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
bool NodeTools::setVarInfo( OutputPort *output_port, void *new_par ) {
	if( output_port == nullptr )
		return false;
	output_port->varPtr = new_par;
	return true;
}
bool NodeTools::setVarInfo( DynamicTypeOutputPort *output_port, void *new_par ) {
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
bool NodeTools::getVarInfo( OutputPort *output_port, Node *&result_input_port_node_parent, VarDirector *&result_var_director, void *&result_var_ptr ) {
	if( output_port == nullptr )
		return false;
	result_input_port_node_parent = output_port->parentNode;
	if( result_input_port_node_parent == nullptr )
		return false;
	result_var_director = result_input_port_node_parent->varDirector;
	result_var_ptr = output_port->varPtr;
	return true;
}
bool NodeTools::getVarInfo( OutputPort *output_port_ptr, VarDirector *&result_var_director, void *&result_var_ptr ) {
	if( output_port_ptr )
		return false;
	result_var_director = output_port_ptr->getVarDirector( );
	result_var_ptr = output_port_ptr->getVarPtr( );
	return result_var_director != nullptr && result_var_ptr != nullptr;
}
bool NodeTools::getVarInfo( InputPort *input_port_ptr, VarDirector *&result_var_director, void *&result_var_ptr ) {
	if( input_port_ptr )
		return false;
	result_var_director = input_port_ptr->getVarDirector( );
	result_var_ptr = input_port_ptr->getVarPtr( );
	return result_var_director != nullptr && result_var_ptr != nullptr;
}
bool NodeTools::getVirtualNormalPath( InputPort *input_port_ptr, QString &resul_normal_path ) {
	if( input_port_ptr == nullptr )
		return false;
	if( getVirtualNormalPath( input_port_ptr->parentNode, resul_normal_path ) == false )
		return false;
	resul_normal_path = resul_normal_path + "\\" + input_port_ptr->getPortName( );
	resul_normal_path = pathTools::normalPathSeparatorToPath( resul_normal_path );
	return true;
}
bool NodeTools::getVirtualNormalPath( OutputPort *output_port_ptr, QString &resul_normal_path ) {
	if( output_port_ptr == nullptr )
		return false;
	if( getVirtualNormalPath( output_port_ptr->parentNode, resul_normal_path ) == false )
		return false;
	resul_normal_path = resul_normal_path + "\\" + output_port_ptr->getPortName( );
	resul_normal_path = pathTools::normalPathSeparatorToPath( resul_normal_path );
	return true;
}
bool NodeTools::getStaticNormalPath( InputPort *input_port_ptr, QString &resul_normal_path ) {
	if( input_port_ptr == nullptr )
		return false;
	if( getStaticNormalPath( input_port_ptr->parentNode, resul_normal_path ) == false )
		return false;
	resul_normal_path = resul_normal_path + "\\" + input_port_ptr->getPortName( );
	resul_normal_path = pathTools::normalPathSeparatorToPath( resul_normal_path );
	return true;
}
bool NodeTools::getStaticNormalPath( OutputPort *output_port_ptr, QString &resul_normal_path ) {

	if( output_port_ptr == nullptr )
		return false;
	if( getStaticNormalPath( output_port_ptr->parentNode, resul_normal_path ) == false )
		return false;
	resul_normal_path = resul_normal_path + "\\" + output_port_ptr->getPortName( );
	resul_normal_path = pathTools::normalPathSeparatorToPath( resul_normal_path );
	return true;
}
bool NodeTools::getVirtualNormalPath( Node *node_ptr, QString &resul_normal_path ) {
	if( node_ptr == nullptr )
		return false;
	resul_normal_path = node_ptr->getVirtualNodeTypeName( );
	resul_normal_path = pathTools::normalPathSeparatorToPath( resul_normal_path );
	return true;
}
bool NodeTools::getStaticNormalPath( Node *node_ptr, QString &resul_normal_path ) {
	if( node_ptr == nullptr )
		return false;
	resul_normal_path = node_ptr->getStaticNodeTypeName( );
	resul_normal_path = pathTools::normalPathSeparatorToPath( resul_normal_path );
	return true;
}
bool NodeTools::getVirtualNormalPathLsstName( InputPort *input_port_ptr, QString &resul_normal_path ) {
	if( getVirtualNormalPath( input_port_ptr, resul_normal_path ) == false )
		return false;
	if( resul_normal_path.isEmpty( ) )
		return false;
	auto list = pathTools::normalPathSeparatorSplitPath( resul_normal_path );
	resul_normal_path = list.last( );
	return true;
}
bool NodeTools::getVirtualNormalPathLsstName( OutputPort *output_port_ptr, QString &resul_normal_path ) {
	if( getVirtualNormalPath( output_port_ptr, resul_normal_path ) == false )
		return false;
	if( resul_normal_path.isEmpty( ) )
		return false;
	auto list = pathTools::normalPathSeparatorSplitPath( resul_normal_path );
	resul_normal_path = list.last( );
	return true;
}
bool NodeTools::getStaticNormalPathLsstName( InputPort *input_port_ptr, QString &resul_normal_path ) {
	if( getStaticNormalPath( input_port_ptr, resul_normal_path ) == false )
		return false;
	if( resul_normal_path.isEmpty( ) )
		return false;
	auto list = pathTools::normalPathSeparatorSplitPath( resul_normal_path );
	resul_normal_path = list.last( );
	return true;
}
bool NodeTools::getStaticNormalPathLsstName( OutputPort *output_port_ptr, QString &resul_normal_path ) {
	if( getStaticNormalPath( output_port_ptr, resul_normal_path ) == false )
		return false;
	if( resul_normal_path.isEmpty( ) )
		return false;
	auto list = pathTools::normalPathSeparatorSplitPath( resul_normal_path );
	resul_normal_path = list.last( );
	return true;
}
bool NodeTools::getVirtualNormalPathLsstName( Node *node_ptr, QString &resul_normal_path ) {
	if( getVirtualNormalPath( node_ptr, resul_normal_path ) == false )
		return false;
	if( resul_normal_path.isEmpty( ) )
		return false;
	auto list = pathTools::normalPathSeparatorSplitPath( resul_normal_path );
	resul_normal_path = list.last( );
	return true;
}
bool NodeTools::getStaticNormalPathLsstName( Node *node_ptr, QString &resul_normal_path ) {
	if( getStaticNormalPath( node_ptr, resul_normal_path ) == false )
		return false;
	if( resul_normal_path.isEmpty( ) )
		return false;
	auto list = pathTools::normalPathSeparatorSplitPath( resul_normal_path );
	resul_normal_path = list.last( );
	return true;
}
bool NodeTools::setVarInfo( OutputPort *output_port, VarDirector *var_director, void *var_ptr ) {
	if( output_port == nullptr )
		return false;
	output_port->varDirectorPtr = var_director;
	output_port->varPtr = var_ptr;
	return true;
}
std::vector< OutputPort * > * NodeTools::getRefPort( InputPort *input_port ) {
	if( input_port == nullptr )
		return nullptr;
	return &input_port->refOutputPortVector;
}
bool NodeTools::setVarInfo( InputPort *input_port, VarDirector *var_director, void *var_ptr ) {
	if( input_port == nullptr )
		return false;
	input_port->inputPortVarDirectorPtr = var_director;
	input_port->inputPortVarPtr = var_ptr;
	return true;
}
bool NodeTools::bindPortVar( const QString &bind_type_name, OutputPort *bind_output_port, void *&result_var_ptr ) {
	if( bind_output_port == nullptr )
		return false;
	auto varDirector = bind_output_port->getVarDirector( );
	if( varDirector == nullptr )
		return false;
	if( varDirector->create( bind_type_name, result_var_ptr ) == false )
		return false;
	if( setVarInfo( bind_output_port, result_var_ptr ) == false ) {
		varDirector->release( result_var_ptr );
		return false;
	}
	return true;
}
bool NodeTools::bindPortVar( const QString &bind_type_name, DynamicTypeOutputPort *bind_output_port, void *&result_var_ptr ) {
	if( bind_output_port == nullptr )
		return false;
	auto varDirector = bind_output_port->getVarDirector( );
	if( varDirector == nullptr )
		return false;
	if( varDirector->create( bind_type_name, result_var_ptr ) == false )
		return false;
	if( setVarInfo( bind_output_port, result_var_ptr ) == false ) {
		varDirector->release( result_var_ptr );
		return false;
	}
	return true;
}
bool NodeTools::appendInputPortType( Node *append_input_port_target_node, InputPort *result_input_port ) {
	return append_input_port_target_node->appendInputPort( result_input_port );
}
bool NodeTools::getNodeTypeName( Node *form_node_type_name, const QString &conver_type_name, QString &result_type_name ) {
	auto varDirector = form_node_type_name->getVarDirector( );
	if( varDirector == nullptr )
		return false;
	if( varDirector->getTypeName( conver_type_name, result_type_name ) == false )
		return false;
	return true;
}
bool NodeTools::createDynamicTypeOutputPort( const QString &dynamic_type_output_port_type_name, const NodeEnum::PortType &port_enum_type, const QString &name, const QString &dynamic_type_var_name, DynamicTypeOutputPort *&result_dynamic_type_output_port_ptr ) {
	if( dynamic_type_output_port_type_name == typeid( DynamicTypeOutputPort ).name( ) ) {
		result_dynamic_type_output_port_ptr = new DynamicTypeOutputPort( port_enum_type, name, dynamic_type_var_name );
		return true;
	}
	return false;
}
bool NodeTools::createDynamicTypeInputPort( const QString &dynamic_type_input_port_type_name, const NodeEnum::PortType &port_enum_type, const QString &name, const QString &dynamic_type_var_name, DynamicTypeInputPort *&result_dynamic_type_input_port_ptr ) {
	if( dynamic_type_input_port_type_name == typeid( DynamicTypeInputPort ).name( ) ) {
		result_dynamic_type_input_port_ptr = new DynamicTypeInputPort( port_enum_type, name, dynamic_type_var_name );
		return true;
	}
	return false;
}
bool NodeTools::finVarDirectorTypeName( const VarDirector *var_type_get_var_director, const QString &org_type_name, QString &result_var_director_type_name ) const {
	return var_type_get_var_director->getTypeName( org_type_name, result_var_director_type_name );
}
bool NodeTools::finVarDirectorVarPtrTypeName( const VarDirector *var_type_get_var_director, const void *find_var_ptr, QString &result_var_director_type_name ) const {
	return var_type_get_var_director->getObjPtrAtTypeName( find_var_ptr, result_var_director_type_name );
}
bool NodeTools::appendOutputPortType( Node *append_output_port_target_node, OutputPort *result_output_port ) {
	return append_output_port_target_node->appendOutputPort( result_output_port );
}
bool NodeTools::appendInputPortType( Node *append_input_port_target_node, DynamicTypeInputPort *result_input_port ) {
	return append_input_port_target_node->appendInputPort( result_input_port );
}
bool NodeTools::appendOutputPortType( Node *append_output_port_target_node, DynamicTypeOutputPort *result_output_port ) {
	return append_output_port_target_node->appendOutputPort( result_output_port );
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
bool NodeTools::getVarInfo( InputPort *input_port, Node *&result_input_port_node_parent, VarDirector *&result_var_director, void *&result_var_ptr ) {

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
bool NodeTools::setVarInfo( InputPort *input_port, void *new_par ) {
	if( input_port == nullptr )
		return false;
	input_port->inputPortVarPtr = new_par;
	return true;
}
bool NodeTools::setVarInfo( DynamicTypeInputPort *input_port, void *new_par ) {
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
