#include "generateNode.h"

#include "../../director/varDirector.h"
GenerateNode::GenerateNode( const QString &node_name ) : Node( node_name ) {

}
GenerateNode::~GenerateNode( ) {

}
bool GenerateNode::init( DrawNodeWidget *parent ) {
	if( Node::init( parent ) == false || initArrayUintyTypeName( generateTypeName ) == false )
		return false;
	return true;
}
bool GenerateNode::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {
	uint64_t *uint64Ptr = nullptr;
	std::vector< uint8_t > converData;
	VarDirector currentVarDirector;
	if( currentVarDirector.init( ) == false )
		return false;
	if( currentVarDirector.create( uint64Ptr ) == false )
		return false;
	if( initVarPtr( ) == false )
		return false;
	void *anyPtr = uint64Ptr;
	if( currentVarDirector.toVar( result_use_count, source_array_ptr, source_array_count, anyPtr ) == false )
		return false;
	auto mode = source_array_count - result_use_count;
	if( mode < *uint64Ptr )
		return false;
	auto offset = source_array_ptr + result_use_count;

	anyPtr = varPtr;
	if( varDirector->toVar( result_use_count, offset, mode, anyPtr ) == false )
		return false;
	result_use_count = offset + result_use_count - source_array_ptr;
	return true;
}
bool GenerateNode::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	uint64_t *uint64Ptr = nullptr;
	std::vector< uint8_t > converData;
	VarDirector currentVarDirector;
	if( currentVarDirector.init( ) == false )
		return false;
	if( currentVarDirector.create( uint64Ptr ) == false )
		return false;
	if( varDirector->toVector( varPtr, converData ) == false )
		return false;
	*uint64Ptr = converData.size( );
	if( currentVarDirector.toVector( uint64Ptr, result_vector_data ) == false )
		return false;
	result_vector_data.append_range( converData );
	return true;
}
