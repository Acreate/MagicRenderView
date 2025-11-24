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

using t_current_unity_type = uint16_t;
bool UInt16UnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	t_current_unity_type buffVar;
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
TypeEnum::Type UInt16UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool UInt16UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
