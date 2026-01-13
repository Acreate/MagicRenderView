#include "uInt64UnityStack.h"

#include <define/macro.h>
#include <tools/infoTool.h>

#include "../../../../director/varDirector.h"

UInt64UnityStack::~UInt64UnityStack( ) {

}
UInt64UnityStack::UInt64UnityStack( ) {
}
bool UInt64UnityStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( 0, uint64_t, tr( "uint64"), tr( "unsigned long long") );
	return true;
}

using t_current_unity_type = uint64_t;
bool UInt64UnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	t_current_unity_type buffVar;
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
TypeEnum::Type UInt64UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool UInt64UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( infoTool::fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
