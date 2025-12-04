#include "generateNode.h"

#include "../../director/varDirector.h"
GenerateNode::GenerateNode( const QString &node_name ) : Node( node_name ) {
	nodeVarDirector = new VarDirector;
}
GenerateNode::~GenerateNode( ) {
	delete nodeVarDirector;
}
bool GenerateNode::init( DrawNodeWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	if( nodeVarDirector->init( ) == false )
		return false;
	if( nodeVarDirector->create( generateVarVector ) == false )
		return false;
	return true;
}
bool GenerateNode::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {
	uint64_t *uint64Ptr = nullptr;
	std::vector< uint8_t > converData;
	if( nodeVarDirector->init( ) == false )
		return false;
	if( nodeVarDirector->create( uint64Ptr ) == false )
		return false;
	if( nodeVarDirector->create( generateVarVector ) == false )
		return false;
	void *anyPtr = uint64Ptr;
	if( nodeVarDirector->toVar( result_use_count, source_array_ptr, source_array_count, anyPtr ) == false ) {
		nodeVarDirector->release( uint64Ptr );
		return false;
	}
	auto mode = source_array_count - result_use_count;
	if( mode < *uint64Ptr ) {
		nodeVarDirector->release( uint64Ptr );
		return false;
	}
	auto offset = source_array_ptr + result_use_count;

	anyPtr = generateVarVector;
	if( nodeVarDirector->toVar( result_use_count, offset, mode, anyPtr ) == false ) {
		nodeVarDirector->release( uint64Ptr );
		return false;
	}
	result_use_count = offset + result_use_count - source_array_ptr;
	return true;
}
bool GenerateNode::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	uint64_t *uint64Ptr = nullptr;
	std::vector< uint8_t > converData;
	if( nodeVarDirector->create( uint64Ptr ) == false )
		return false;
	if( nodeVarDirector->toVector( generateVarVector, converData ) == false ) {
		nodeVarDirector->release( uint64Ptr );
		return false;
	}
	*uint64Ptr = converData.size( );
	if( nodeVarDirector->toVector( uint64Ptr, result_vector_data ) == false ) {
		nodeVarDirector->release( uint64Ptr );
		return false;
	}
	result_vector_data.append_range( converData );
	return true;
}
