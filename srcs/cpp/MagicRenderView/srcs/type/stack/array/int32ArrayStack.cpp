#include "int32ArrayStack.h"

#include <define/macro.h>
Int32ArrayStack::~Int32ArrayStack( ) {

}
Int32ArrayStack::Int32ArrayStack( ) {
	Stack_Type_Name( , std::vector< int32_t >, "vector<int32_t>", "int32_t[]", "int32_tArray", "vector<int32>", "int32[]", "int32Array" );
}

uint64_t Int32ArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	uint64_t arrayCount = 0;
	count = fillTypeVectorAtVar< uint64_t >( offset, mod, &arrayCount );
	if( count == 0 )
		return 0;
	offset = offset + count;
	mod = mod - count;
	std::vector< int32_t > buffVar( arrayCount );

	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index ) {
		int32_t *ptr = arrayPtr + index;
		count = fillTypeVectorAtVar< int32_t >( offset, mod, ptr );
		if( count == 0 )
			return 0;
		offset = offset + count;
		mod = mod - count;
	}

	auto createPtr = ( std::vector< int32_t > * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type Int32ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t Int32ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	std::vector< int32_t > *vector = ( std::vector< int32_t > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	count = fillTypeVarAtVector< uint64_t >( &arraySize, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index ) {
		int32_t *ptr = arrayPtr + index;
		count = fillTypeVarAtVector< int32_t >( ptr, buff );
		if( count == 0 )
			return 0;
		result_data.append_range( buff );
	}
	return result_data.size( );
}
