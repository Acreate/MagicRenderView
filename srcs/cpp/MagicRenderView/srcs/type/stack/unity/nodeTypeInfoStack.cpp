#include "nodeTypeInfoStack.h"

#include "../../../define/macro.h"
#include "../../../node/nodeType/nodeTypeInfo.h"
#include "../../../tools/infoTool.h"

NodeTypeInfoStack::~NodeTypeInfoStack( ) {

}
bool NodeTypeInfoStack::init( ) {
	Stack_Type_Name( , NodeTypeInfo, "NodeTypeInfo" );
	return true;
}
NodeTypeInfoStack::NodeTypeInfoStack( ) {
}

using t_current_unity_type = NodeTypeInfo;
bool NodeTypeInfoStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	//t_current_unity_type buffVar;
	//if( infoTool::fillTypeVectorAtVar< t_current_unity_type >( result_count, obj_start_ptr, obj_memory_size, &buffVar ) == false )
	//	return false;
	//if( hasVarPtr( result_obj_ptr ) == false ) {
	//	void *sourcePtr = nullptr;
	//	if( createTypePtr( sourcePtr ) == false )
	//		return false;
	//	auto createPtr = ( t_current_unity_type * ) sourcePtr;
	//	*createPtr = buffVar;
	//	result_obj_ptr = createPtr;
	//	return true;
	//}

	//auto createPtr = ( t_current_unity_type * ) result_obj_ptr;
	//*createPtr = buffVar;
	return true;
}
TypeEnum::Type NodeTypeInfoStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool NodeTypeInfoStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	//if( infoTool::fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
	//	return false;
	return true;
}
