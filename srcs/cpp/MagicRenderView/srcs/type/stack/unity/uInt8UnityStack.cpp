#include "uInt8UnityStack.h"

UInt8UnityStack::~UInt8UnityStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( uint8_t * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
UInt8UnityStack::UInt8UnityStack( ) {
	Stack_Type_Name( uint8_t, "uint8", "unsigned char" );
}
void * UInt8UnityStack::createTypePtr( ) {
	auto createObjPtr = new uint8_t;
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
bool UInt8UnityStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( uint8_t * ) arrayPtr[ index ];
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

uint64_t UInt8UnityStack::toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return 0;
}
uint64_t UInt8UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) {
	return 0;
}
TypeEnum::Type UInt8UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
