#include "anyPtrArrayStack.h"

#include "../../../define/macro.h"
#include "../../../director/varDirector.h"
#include "../../../tools/infoTool.h"

AnyPtrArrayStack::~AnyPtrArrayStack( ) {

}
AnyPtrArrayStack::AnyPtrArrayStack( ) {

}

bool AnyPtrArrayStack::init( ) {
	Stack_Type_Name( , std::vector< void * >, "vector< void * >", "void *[]", "voidPtrArray" );
	return true;
}
using t_current_unity_type = void *;
bool AnyPtrArrayStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t arrayCount = 0;
	if( infoTool::fillTypeVectorAtVar< uint64_t >( result_count, obj_start_ptr, obj_memory_size, &arrayCount ) == false )
		return false;
	auto offset = obj_start_ptr + result_count;
	auto mod = obj_memory_size - result_count;
	std::vector< t_current_unity_type > buffVar( arrayCount );

	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index, offset = offset + result_count,
		mod = mod - result_count )
		if( varDirector.toVar( result_count, offset, mod, *( arrayPtr + index ) ) == false )
			return false;
	result_count = offset - obj_start_ptr;
	if( hasVarPtr( result_obj_ptr ) == false ) {
		void *sourcePtr;
		if( createTypePtr( sourcePtr ) == false )
			return false;
		auto createPtr = ( std::vector< t_current_unity_type > * ) sourcePtr;
		*createPtr = buffVar;
		result_obj_ptr = createPtr;
		return true;
	}
	auto createPtr = ( std::vector< t_current_unity_type > * ) result_obj_ptr;
	*createPtr = buffVar;
	return true;
}
TypeEnum::Type AnyPtrArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
bool AnyPtrArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	std::vector< t_current_unity_type > *vector = ( std::vector< t_current_unity_type > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	if( infoTool::fillTypeVarAtVector< uint64_t >( &arraySize, buff ) == false )
		return false;

	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	result_data.append_range( buff );
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index )
		if( varDirector.toVector( *( arrayPtr + index ), buff ) == false )
			return false;
		else
			result_data.append_range( buff );
	return true;
}
