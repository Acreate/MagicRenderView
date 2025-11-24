#include "float32UnityStack.h"

#include <define/macro.h>
Float32UnityStack::~Float32UnityStack( ) {

}
bool Float32UnityStack::init( ) {
	Stack_Type_Name( 0.0f, float, "float32", "double32", "float_t" );
	return true;
}
Float32UnityStack::Float32UnityStack( ) {
}

using t_current_unity_type = float;
bool Float32UnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	float buffVar;
	if( fillTypeVectorAtVar< t_current_unity_type >( result_count, obj_start_ptr, obj_memory_size, &buffVar ) == false )
		return false;
	void *sourcePtr;
	if( createTypePtr( sourcePtr ) == false )
		return false;
	auto createPtr = ( t_current_unity_type * ) sourcePtr;
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return true;
}
TypeEnum::Type Float32UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool Float32UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
