#include "int16UnityStack.h"

#include <define/macro.h>
Int16UnityStack::~Int16UnityStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( int16_t * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
Int16UnityStack::Int16UnityStack( ) {
	Stack_Type_Name( int16_t, "int16", "short" );
}
void * Int16UnityStack::createTypePtr( ) {
	auto createObjPtr = new int16_t( 0 );
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
bool Int16UnityStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( int16_t * ) arrayPtr[ index ];
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

uint64_t Int16UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	int16_t buffVar;
	count = fillTypeVectorAtVar< int16_t >( offset, mod, &buffVar );
	if( count == 0 )
		return 0;
	offset = offset + count;
	auto createPtr = ( int16_t * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type Int16UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
uint64_t Int16UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( buff );
	if( count == 0 )
		return 0;
	result_data.clear( );
	result_data.append_range( buff );
	count = fillTypeVarAtVector< int16_t >( obj_start_ptr, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
