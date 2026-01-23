#include "float32UnityStack.h"

#include <define/macro.h>
#include <tools/infoTool.h>

#include "../../../../director/varDirector.h"

Float32UnityStack::~Float32UnityStack( ) {

}
bool Float32UnityStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( 0.0f, float, tr ("float32"), tr ("double32"), tr ("float_t") );
	return true;
}
Float32UnityStack::Float32UnityStack( ) {
}

using t_current_unity_type = float;
bool Float32UnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	float buffVar;
	if( infoTool::fillTypeVectorAtVar< t_current_unity_type >( result_count, obj_start_ptr, obj_memory_size, &buffVar ) == false )
		return false;
	if( hasVarPtr( result_obj_ptr ) == false ) {
		t_current_unity_type *sourcePtr = nullptr;
		if( varDirector->create( sourcePtr ) == false || sourcePtr == nullptr )
			return false;
		*sourcePtr = buffVar;
		result_obj_ptr = sourcePtr;
		return true;
	}

	auto createPtr = ( t_current_unity_type * ) result_obj_ptr;
	*createPtr = buffVar;
	return true;
}
TypeEnum::Type Float32UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool Float32UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( infoTool::fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
