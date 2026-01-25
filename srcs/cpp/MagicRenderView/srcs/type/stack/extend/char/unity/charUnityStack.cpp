#include "charUnityStack.h"

#include <define/stackTypeMacro.h>
#include <tools/infoTool.h>
#include <director/varDirector.h>
#include <QChar>
using t_current_unity_type = QChar;
CharUnityStack::~CharUnityStack( ) {

}
bool CharUnityStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( '\0', QChar, tr ("Char"), tr("char" ) );
	return true;
}
CharUnityStack::CharUnityStack( ) {
}

bool CharUnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
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
TypeEnum::Type CharUnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool CharUnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	if( infoTool::fillTypeVarAtVector< t_current_unity_type >( obj_start_ptr, result_data ) == false )
		return false;
	return true;
}
