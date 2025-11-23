#include "uInt16UnityStack.h"

#include <define/macro.h>
UInt16UnityStack::~UInt16UnityStack( ) {

}
bool UInt16UnityStack::init( ) {
	Stack_Type_Name( 0, uint16_t, "uint16", "unsigned short" );
	return true;
}
UInt16UnityStack::UInt16UnityStack( ) {

}

uint64_t UInt16UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	uint16_t buffVar;
	count = fillTypeVectorAtVar< uint16_t >( offset, mod, &buffVar );
	if( count == 0 )
		return 0;
	offset = offset + count;
	auto createPtr = ( uint16_t * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type UInt16UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
uint64_t UInt16UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	count = fillTypeVarAtVector< uint16_t >( obj_start_ptr, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
