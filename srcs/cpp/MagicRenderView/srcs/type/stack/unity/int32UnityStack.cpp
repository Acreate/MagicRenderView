#include "int32UnityStack.h"

#include <define/macro.h>
Int32UnityStack::~Int32UnityStack( ) {

}
bool Int32UnityStack::init( ) {
	Stack_Type_Name( 0, int32_t, "int32", "int" );
	return true;
}
Int32UnityStack::Int32UnityStack( ) {
}

uint64_t Int32UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	int32_t buffVar;
	count = fillTypeVectorAtVar< int32_t >( offset, mod, &buffVar );
	if( count == 0 )
		return 0;
	offset = offset + count;
	auto createPtr = ( int32_t * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type Int32UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
uint64_t Int32UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	count = fillTypeVarAtVector< int32_t >( obj_start_ptr, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
