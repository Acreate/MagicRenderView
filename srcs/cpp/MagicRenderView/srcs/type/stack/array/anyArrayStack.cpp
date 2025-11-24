#include "anyArrayStack.h"

#include <app/application.h>

#include <define/macro.h>

#include <director/varDirector.h>

AnyArrayStack::~AnyArrayStack( ) {

}
bool AnyArrayStack::init( ) {
	Stack_Type_Name( , std::vector< void * >, "vector< void * >", "void *[]", "voidPtrArray" );
	return true;
}
AnyArrayStack::AnyArrayStack( ) {

}

bool AnyArrayStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t arrayCount = 0;
	if( fillTypeVectorAtVar< uint64_t >( result_count, obj_start_ptr, obj_memory_size, &arrayCount ) == false )
		return false;
	auto offset = obj_start_ptr + result_count;
	auto mod = obj_memory_size - result_count;
	std::vector< void * > buffVar( arrayCount );

	auto varDirector = Application::getInstancePtr( )->getVarDirector( );
	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index, offset = offset + result_count,
		mod = mod - result_count )
		if( varDirector->toVar( result_count, offset, mod, ( arrayPtr + index ) ) == false )
			return false;
	void *sourcePtr;
	if( createTypePtr( sourcePtr ) == false )
		return false;
	auto createPtr = ( std::vector< void * > * ) sourcePtr;
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	result_count = offset - obj_start_ptr;
	return true;
}
TypeEnum::Type AnyArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
bool AnyArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	std::vector< void * > *vector = ( std::vector< void * > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	if( fillTypeVarAtVector< uint64_t >( &arraySize, buff ) == false )
		return false;
	auto varDirector = Application::getInstancePtr( )->getVarDirector( );
	result_data.append_range( buff );
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index )
		if( varDirector->toVector( *( arrayPtr + index ), buff ) == false )
			return false;
		else
			result_data.append_range( buff );
	return true;
}
