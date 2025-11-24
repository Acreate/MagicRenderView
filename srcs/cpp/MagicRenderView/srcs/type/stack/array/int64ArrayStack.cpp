#include "int64ArrayStack.h"

#include <define/macro.h>
Int64ArrayStack::~Int64ArrayStack( ) {

}
bool Int64ArrayStack::init( ) {
	Stack_Type_Name( , std::vector< int64_t >, "vector<int64_t>", "int64_t[]", "int64_tArray", "vector<int64>", "int64[]", "int64Array" );
	return true;
}
Int64ArrayStack::Int64ArrayStack( ) {
}

using t_current_unity_type = int64_t;
bool Int64ArrayStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	uint64_t arrayCount = 0;
	if( fillTypeVectorAtVar< uint64_t >( result_count, obj_start_ptr, obj_memory_size, &arrayCount ) == false )
		return false;
	auto offset = obj_start_ptr + result_count;
	auto mod = obj_memory_size - result_count;
	std::vector< t_current_unity_type > buffVar( arrayCount );
	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index, offset = offset + result_count, mod = mod - result_count )
		if( fillTypeVectorAtVar< t_current_unity_type >( result_count, offset, mod, arrayPtr + index ) == false )
			return false;
	result_count = offset - obj_start_ptr;
	if( hasVarPtr( result_obj_ptr ) == false ) {
		void *sourcePtr;
		if( createTypePtr( sourcePtr ) == false )
			return false;
		auto createPtr = ( std::vector< t_current_unity_type > * ) sourcePtr;
		*createPtr = buffVar;
		result_obj_ptr = createPtr;
		return true;
	}
	auto createPtr = ( std::vector< t_current_unity_type > * ) result_obj_ptr;
	*createPtr = buffVar;
	return true;
}
TypeEnum::Type Int64ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
bool Int64ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< t_current_unity_type > *vector = ( std::vector< t_current_unity_type > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	if( fillTypeVarAtVector< uint64_t >( &arraySize, result_data ) == false )
		return false;
	std::vector< uint8_t > buff;
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index )
		if( fillTypeVarAtVector< t_current_unity_type >( arrayPtr + index, buff ) == false )
			return false;
		else
			result_data.append_range( buff );
	return true;
}
