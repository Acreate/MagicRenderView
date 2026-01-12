#include "timeUnityStack.h"

#include <define/macro.h>
#include <tools/infoTool.h>
#include <director/varDirector.h>
#include <QTime>

using t_current_unity_type = QTime;
TimeUnityStack::~TimeUnityStack( ) {
	delete dateTimeFormat;
}
bool TimeUnityStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( , QDateTime, "QDateTime", "DateTime", "Date", "Time" );
	return true;
}
TimeUnityStack::TimeUnityStack( ) {
	dateTimeFormat = new QString( "hh时mm分ss秒.zzz" );
}

bool TimeUnityStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	QString dateTimeString;
	t_current_unity_type buffVar;
	if( infoTool::fillTypeVectorAtVar< >( result_count, obj_start_ptr, obj_memory_size, &dateTimeString ) == false )
		return false;
	buffVar = QTime::fromString( dateTimeString, *dateTimeFormat );
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
TypeEnum::Type TimeUnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool TimeUnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	t_current_unity_type *converVarPtr = ( t_current_unity_type * ) obj_start_ptr;
	QString dateTimeString = converVarPtr->toString( *dateTimeFormat );
	if( infoTool::fillTypeVarAtVector< QString >( &dateTimeString, result_data ) == false )
		return false;
	return true;
}
