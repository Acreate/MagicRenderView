#include "int8UnityStack.h"

Int8UnityStack::~Int8UnityStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( int8_t * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
Int8UnityStack::Int8UnityStack( ) {
	Stack_Type_Name( int8_t, "int8", "char" );
}
void * Int8UnityStack::createTypePtr( ) {
	auto createObjPtr = new int8_t;
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
bool Int8UnityStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( int8_t * ) arrayPtr[ index ];
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

uint64_t Int8UnityStack::toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return 0;
}
uint64_t Int8UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) {
	return 0;
}
TypeEnum::Type Int8UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
