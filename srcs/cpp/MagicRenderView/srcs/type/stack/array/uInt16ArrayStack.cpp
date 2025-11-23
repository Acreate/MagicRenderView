#include "uInt16ArrayStack.h"

#include <define/macro.h>
UInt16ArrayStack::~UInt16ArrayStack( ) {

}
bool UInt16ArrayStack::init( ) {
	Stack_Type_Name( , std::vector< uint16_t >, "vector<uint16_t>", "uint16_t[]", "uint16_tArray", "vector<uint16>", "uint16[]", "uint16Array" );
	return true;
}
UInt16ArrayStack::UInt16ArrayStack( ) {

}

uint64_t UInt16ArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

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
	std::vector< uint16_t > buffVar( arrayCount );

	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index ) {
		uint16_t *ptr = arrayPtr + index;
		count = fillTypeVectorAtVar< uint16_t >( offset, mod, ptr );
		if( count == 0 )
			return 0;
		offset = offset + count;
		mod = mod - count;
	}

	auto createPtr = ( std::vector< uint16_t > * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type UInt16ArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t UInt16ArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	std::vector< uint16_t > *vector = ( std::vector< uint16_t > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	count = fillTypeVarAtVector< uint64_t >( &arraySize, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index ) {
		uint16_t *ptr = arrayPtr + index;
		count = fillTypeVarAtVector< uint16_t >( ptr, buff );
		if( count == 0 )
			return 0;
		result_data.append_range( buff );
	}
	return result_data.size( );
}
