#include "uInt64ArrayStack.h"

#include <define/macro.h>
UInt64ArrayStack::~UInt64ArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( std::vector< uint64_t > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
UInt64ArrayStack::UInt64ArrayStack( ) {
	Stack_Type_Name( std::vector<uint64_t>, "vector<uint64_t>", "uint64_t[]", "uint64_tArray", "vector<uint64>", "uint64[]", "uint64Array" );
}
void * UInt64ArrayStack::createTypePtr( ) {
	auto createObjPtr = new std::vector< uint64_t >;
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] ) {
			arrayPtr[ index ] = createObjPtr;
			return createObjPtr;
		}
	allVarPtrVector.emplace_back( createObjPtr );
	return createObjPtr;
}
bool UInt64ArrayStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( std::vector< uint64_t > * ) arrayPtr[ index ];
			count -= 1;
			for( ; index < count; --count )
				if( nullptr == arrayPtr[ count ] ) {
					arrayPtr[ index ] = arrayPtr[ count ];
					return true;
				}
			return true;
		}
	return false;
}

uint64_t UInt64ArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
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
	std::vector< uint64_t > buffVar( arrayCount );

	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index ) {
		uint64_t *ptr = arrayPtr + index;
		count = fillTypeVectorAtVar< uint64_t >( offset, mod, ptr );
		if( count == 0 )
			return 0;
		offset = offset + count;
		mod = mod - count;
	}

	auto createPtr = ( std::vector< uint64_t > * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type UInt64ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t UInt64ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	std::vector< uint64_t > *vector = ( std::vector< uint64_t > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	count = fillTypeVarAtVector< uint64_t >( &arraySize, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index ) {
		uint64_t *ptr = arrayPtr + index;
		count = fillTypeVarAtVector< uint64_t >( ptr, buff );
		if( count == 0 )
			return 0;
		result_data.append_range( buff );
	}
	return result_data.size( );
}
