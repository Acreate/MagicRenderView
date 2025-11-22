#include "anyArrayStack.h"

#include <define/macro.h>

AnyArrayStack::~AnyArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( std::vector< void * > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
AnyArrayStack::AnyArrayStack( ) {
	Stack_Type_Name( std::vector< void * >, "vector< void * >", "void *[]", "voidPtrArray" );
}
void * AnyArrayStack::createTypePtr( ) {
	auto createObjPtr = new std::vector< void * >;
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
bool AnyArrayStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( std::vector< void * > * ) arrayPtr[ index ];
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

uint64_t AnyArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	return 0;
}
TypeEnum::Type AnyArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t AnyArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return 0;
}
