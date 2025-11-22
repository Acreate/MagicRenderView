#include "uInt64UnityStack.h"

#include <define/macro.h>
UInt64UnityStack::~UInt64UnityStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( uint64_t * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
UInt64UnityStack::UInt64UnityStack( ) {
	Stack_Type_Name( uint64_t, "uint64", "unsigned long long" );
}
void * UInt64UnityStack::createTypePtr( ) {
	auto createObjPtr = new uint64_t( 0 );
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
bool UInt64UnityStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( uint64_t * ) arrayPtr[ index ];
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

uint64_t UInt64UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) {
	return 0;
}
TypeEnum::Type UInt64UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
uint64_t UInt64UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return toVector< uint64_t >( obj_start_ptr, result_data );
}
