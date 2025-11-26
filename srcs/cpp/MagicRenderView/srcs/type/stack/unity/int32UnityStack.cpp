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

using t_current_unity_type = int32_t;
bool Int32UnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	t_current_unity_type buffVar;
	if( infoTool::fillTypeVectorAtVar< t_current_unity_type >( result_count, obj_start_ptr, obj_memory_size, &buffVar ) == false )
		return false;
	if( hasVarPtr( result_obj_ptr ) == false ) {
		void *sourcePtr = nullptr;
		if( createTypePtr( sourcePtr ) == false )
			return false;
		auto createPtr = ( t_current_unity_type * ) sourcePtr;
		*createPtr = buffVar;
		result_obj_ptr = createPtr;
		return true;
	}

	auto createPtr = ( t_current_unity_type * ) result_obj_ptr;
	*createPtr = buffVar;
	return true;
}
TypeEnum::Type Int32UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool Int32UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( infoTool::fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
