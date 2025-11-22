#include "int32ArrayStack.h"

#include <define/macro.h>
Int32ArrayStack::~Int32ArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( std::vector< int32_t > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
Int32ArrayStack::Int32ArrayStack( ) {
	Stack_Type_Name( std::vector< int32_t >, "vector<int32_t>", "int32_t[]", "int32_tArray", "vector<int32>", "int32[]", "int32Array" );
}
void * Int32ArrayStack::createTypePtr( ) {
	auto createObjPtr = new std::vector< int32_t >;
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
bool Int32ArrayStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( std::vector< int32_t > * ) arrayPtr[ index ];
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

uint64_t Int32ArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) {
	return 0;
}
TypeEnum::Type Int32ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t Int32ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {

	return 0;
}
