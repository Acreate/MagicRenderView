#include "colorUnityStack.h"

#include <define/stackTypeMacro.h>
#include <tools/infoTool.h>
#include <director/varDirector.h>
#include <QColor>
using t_current_unity_type = QColor;
ColorUnityStack::~ColorUnityStack( ) {

}
bool ColorUnityStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( , QColor,tr ("Color"),tr ("color" ));
	return true;
}
ColorUnityStack::ColorUnityStack( ) {
}

bool ColorUnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
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
TypeEnum::Type ColorUnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool ColorUnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( infoTool::fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
