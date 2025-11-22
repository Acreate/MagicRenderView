#include "int64ArrayStack.h"

Int64ArrayStack::~Int64ArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( std::vector< int64_t > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
Int64ArrayStack::Int64ArrayStack( ) {
	Stack_Type_Name( std::vector< int64_t >, "vector<int64_t>", "int64_t[]", "int64_tArray", "vector<int64>", "int64[]", "int64Array" );
}
void * Int64ArrayStack::createTypePtr( ) {
	auto createObjPtr = new std::vector< int64_t >;
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
bool Int64ArrayStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( std::vector< int64_t > * ) arrayPtr[ index ];
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

uint64_t Int64ArrayStack::toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return 0;
}
uint64_t Int64ArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) {
	return 0;
}
TypeEnum::Type Int64ArrayStack::getType( ) {
	return TypeEnum::Type::Unity;
}
