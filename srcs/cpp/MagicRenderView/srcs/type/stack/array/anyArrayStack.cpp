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

uint64_t AnyArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	uint64_t arrayCount = 0;
	count = fillTypeVectorAtVar< uint64_t >( offset, mod, &arrayCount );
	if( count == 0 )
		return 0;
	offset = offset + count;
	mod = mod - count;
	std::vector< void * > buffVar( arrayCount );

	auto varDirector = Application::getInstancePtr( )->getVarDirector( );
	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index ) {
		void **targetVarPtr = arrayPtr + index;
		count = varDirector->toVar( offset, mod, targetVarPtr );
		if( count == 0 )
			return 0;
		offset = offset + count;
		mod = mod - count;
	}

	auto createPtr = ( std::vector< void * > * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type AnyArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t AnyArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	std::vector< void * > *vector = ( std::vector< void * > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	count = fillTypeVarAtVector< uint64_t >( &arraySize, buff );
	if( count == 0 )
		return 0;
	auto varDirector = Application::getInstancePtr( )->getVarDirector( );
	result_data.append_range( buff );
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index ) {
		void **ptr = arrayPtr + index;
		count = varDirector->toVector( *ptr, buff );
		if( count == 0 )
			return 0;
		result_data.append_range( buff );
	}
	return result_data.size( );
}
