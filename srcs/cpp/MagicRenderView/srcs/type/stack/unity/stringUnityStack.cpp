#include "stringUnityStack.h"

#include <define/macro.h>
StringUnityStack::~StringUnityStack( ) {

}
bool StringUnityStack::init( ) {
	Stack_Type_Name( "", QString, "string" );
	return true;
}
StringUnityStack::StringUnityStack( ) {
}

using t_current_unity_type = QString;
bool StringUnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	t_current_unity_type buffVar;
	if( fillTypeVectorAtVar< t_current_unity_type >( result_count, obj_start_ptr, obj_memory_size, &buffVar ) == false )
		return false;
	auto createPtr = ( t_current_unity_type * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return true;
}
TypeEnum::Type StringUnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool StringUnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
