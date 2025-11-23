#include "int8UnityStack.h"

#include <define/macro.h>
Int8UnityStack::~Int8UnityStack( ) {

}
Int8UnityStack::Int8UnityStack( ) {
	Stack_Type_Name( 0, int8_t, "int8", "char" );
}

uint64_t Int8UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	int8_t buffVar;
	count = fillTypeVectorAtVar< int8_t >( offset, mod, &buffVar );
	if( count == 0 )
		return 0;
	offset = offset + count;
	auto createPtr = ( int8_t * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type Int8UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
uint64_t Int8UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	count = fillTypeVarAtVector< int8_t >( obj_start_ptr, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
