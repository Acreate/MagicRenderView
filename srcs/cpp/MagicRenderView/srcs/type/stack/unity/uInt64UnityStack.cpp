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

uint64_t UInt64UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	uint64_t buffVar;
	count = fillTypeVectorAtVar< uint64_t >( offset, mod, &buffVar );
	if( count == 0 )
		return 0;
	offset = offset + count;
	auto createPtr = ( uint64_t * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type UInt64UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
uint64_t UInt64UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( buff );
	if( count == 0 )
		return 0;
	result_data.clear( );
	result_data.append_range( buff );
	count = fillTypeVarAtVector< uint64_t >( obj_start_ptr, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
