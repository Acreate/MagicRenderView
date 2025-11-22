#include "float32ArrayStack.h"

#include <define/macro.h>
Float32ArrayStack::~Float32ArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( std::vector< float > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
Float32ArrayStack::Float32ArrayStack( ) {
	Stack_Type_Name( std::vector<float>, "vector<float>", "float[]", "floatArray", "vector<double32>", "double32[]", "double32Array", "vector<float32>", "float32[]", "float32Array" );
}
void * Float32ArrayStack::createTypePtr( ) {
	auto createObjPtr = new std::vector< float >;
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
bool Float32ArrayStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( std::vector< float > * ) arrayPtr[ index ];
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

uint64_t Float32ArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	return 0;
}
TypeEnum::Type Float32ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t Float32ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return 0;
}
