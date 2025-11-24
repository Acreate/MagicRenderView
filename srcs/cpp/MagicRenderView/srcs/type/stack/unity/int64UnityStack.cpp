#include "int64UnityStack.h"

#include <define/macro.h>
Int64UnityStack::~Int64UnityStack( ) {

}
bool Int64UnityStack::init( ) {
	Stack_Type_Name( 0, int64_t, "int64", "long long" );
	return true;
}
Int64UnityStack::Int64UnityStack( ) {
}

using t_current_unity_type = int64_t;
bool Int64UnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	t_current_unity_type buffVar;
	if( fillTypeVectorAtVar< t_current_unity_type >( result_count, obj_start_ptr, obj_memory_size, &buffVar ) == false )
		return false;
	auto createPtr = ( t_current_unity_type * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return true;
}
TypeEnum::Type Int64UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool Int64UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
