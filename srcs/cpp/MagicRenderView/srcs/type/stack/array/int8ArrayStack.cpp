#include "int8ArrayStack.h"

#include <define/macro.h>
Int8ArrayStack::~Int8ArrayStack( ) {

}
Int8ArrayStack::Int8ArrayStack( ) {
	Stack_Type_Name( std::vector<int8_t>, "vector<int8_t>", "int8_t[]", "int8_tArray", "vector<int8>", "int8[]", "int8Array" );
	newObjTypeFunction = [] {
		return new std::vector< int8_t >;
	};
	deleteObjTypeFunction = [] ( void *delete_obj_ptr ) {
		delete ( std::vector< int8_t > * ) delete_obj_ptr;
		return true;
	};
}

uint64_t Int8ArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

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
	std::vector< int8_t > buffVar( arrayCount );

	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index ) {
		int8_t *ptr = arrayPtr + index;
		count = fillTypeVectorAtVar< int8_t >( offset, mod, ptr );
		if( count == 0 )
			return 0;
		offset = offset + count;
		mod = mod - count;
	}

	auto createPtr = ( std::vector< int8_t > * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type Int8ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t Int8ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	std::vector< int8_t > *vector = ( std::vector< int8_t > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	count = fillTypeVarAtVector< uint64_t >( &arraySize, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index ) {
		int8_t *ptr = arrayPtr + index;
		count = fillTypeVarAtVector< int8_t >( ptr, buff );
		if( count == 0 )
			return 0;
		result_data.append_range( buff );
	}
	return result_data.size( );
}
