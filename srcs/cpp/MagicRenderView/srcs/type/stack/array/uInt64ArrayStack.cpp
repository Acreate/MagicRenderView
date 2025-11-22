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
	return 0;
}
TypeEnum::Type UInt64ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t UInt64ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return 0;
}
