#include "int16ArrayStack.h"

#include <define/macro.h>
#include <tools/infoTool.h>

Int16ArrayStack::~Int16ArrayStack( ) {

}
bool Int16ArrayStack::init( ) {
	Stack_Type_Name( , std::vector< int16_t >, "vector<int16_t>", "int16_t[]", "int16_tArray", "vector<int16>", "int16[]", "int16Array" );
	return true;
}
Int16ArrayStack::Int16ArrayStack( ) {
}

using t_current_unity_type = int16_t;
bool Int16ArrayStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	uint64_t arrayCount = 0;
	if( infoTool::fillTypeVectorAtVar< uint64_t >( result_count, obj_start_ptr, obj_memory_size, &arrayCount ) == false )
		return false;
	auto offset = obj_start_ptr + result_count;
	auto mod = obj_memory_size - result_count;
	std::vector< t_current_unity_type > buffVar( arrayCount );
	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index, offset = offset + result_count, mod = mod - result_count )
		if( infoTool::fillTypeVectorAtVar< t_current_unity_type >( result_count, offset, mod, arrayPtr + index ) == false )
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
TypeEnum::Type Int16ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
bool Int16ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< t_current_unity_type > *vector = ( std::vector< t_current_unity_type > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	if( infoTool::fillTypeVarAtVector< uint64_t >( &arraySize, result_data ) == false )
		return false;
	std::vector< uint8_t > buff;
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index )
		if( infoTool::fillTypeVarAtVector< t_current_unity_type >( arrayPtr + index, buff ) == false )
			return false;
		else
			result_data.append_range( buff );
	return true;
}
