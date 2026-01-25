#include "dateArrayStack.h"

#include <define/stackTypeMacro.h>
#include <tools/infoTool.h>

#include <director/varDirector.h>
#include <QDate>

using t_current_unity_type = QDate;
DateArrayStack::~DateArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] )
			delete ( std::vector< t_current_unity_type > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
	delete dateTimeFormat;
}
bool DateArrayStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( , std::vector< QDate >, tr ("vector<QDate>"), tr ("QDate[]"), tr ("QDateArray"), tr("vector<Date>"), tr("Date[]"), tr ("DateArray" ) );
	return true;
}
DateArrayStack::DateArrayStack( ) {
	dateTimeFormat = new QString( "yyyy年MM月dd日" );
}

bool DateArrayStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	uint64_t arrayCount = 0;
	if( infoTool::fillTypeVectorAtVar< uint64_t >( result_count, obj_start_ptr, obj_memory_size, &arrayCount ) == false )
		return false;
	auto offset = obj_start_ptr + result_count;
	auto mod = obj_memory_size - result_count;
	std::vector< t_current_unity_type > buffVar( arrayCount );
	auto arrayPtr = buffVar.data( );
	QString dateTimeString;
	for( size_t index = 0; index < arrayCount; ++index, offset = offset + result_count, mod = mod - result_count ) {
		if( infoTool::fillTypeVectorAtVar< >( result_count, offset, mod, &dateTimeString ) == false )
			return false;
		arrayPtr[ index ] = QDate::fromString( dateTimeString, *dateTimeFormat );
	}
	result_count = offset - obj_start_ptr;
	if( hasVarPtr( result_obj_ptr ) == false ) {
		std::vector< t_current_unity_type > *sourcePtr = nullptr;
		if( varDirector->create( sourcePtr ) == false || sourcePtr == nullptr )
			return false;
		*sourcePtr = buffVar;
		result_obj_ptr = sourcePtr;
		return true;
	}
	auto createPtr = ( std::vector< t_current_unity_type > * ) result_obj_ptr;
	*createPtr = buffVar;
	return true;
}
TypeEnum::Type DateArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
bool DateArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< t_current_unity_type > *vector = ( std::vector< t_current_unity_type > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	if( infoTool::fillTypeVarAtVector< uint64_t >( &arraySize, result_data ) == false )
		return false;
	std::vector< uint8_t > buff;
	auto arrayPtr = vector->data( );
	QString dateTimeString;
	for( size_t index = 0; index < arraySize; ++index ) {
		dateTimeString = arrayPtr[ index ].toString( *dateTimeFormat );
		if( infoTool::fillTypeVarAtVector< QString >( &dateTimeString, buff ) == false )
			return false;
		else
			result_data.append_range( buff );
	}
	return true;
}
