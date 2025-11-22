#include "int16ArrayStack.h"

#include <define/macro.h>
Int16ArrayStack::~Int16ArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( std::vector< int16_t > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
Int16ArrayStack::Int16ArrayStack( ) {
	Stack_Type_Name( std::vector< int16_t >, "vector<int16_t>", "int16_t[]", "int16_tArray", "vector<int16>", "int16[]", "int16Array" );
}
void * Int16ArrayStack::createTypePtr( ) {
	auto createObjPtr = new std::vector< int16_t >;
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
bool Int16ArrayStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( std::vector< int16_t > * ) arrayPtr[ index ];
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

uint64_t Int16ArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	return 0;
}
TypeEnum::Type Int16ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t Int16ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return 0;
}
