#include "nodeTypeInfoPtrArrayStack.h"

#include <define/macro.h>
#include <director/varDirector.h>
#include <tools/infoTool.h>

#include <node/nodeType/nodeTypeInfo.h>

using t_current_unity_type = NodeTypeInfo *;
NodeTypeInfoPtrArrayStack::~NodeTypeInfoPtrArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] ) {
			std::vector< t_current_unity_type > *vector = ( std::vector< t_current_unity_type > * ) arrayPtr[ index ];
			size_t voidPtrArrayCount = vector->size( );
			auto voidPtrArrayPtr = vector->data( );
			size_t voidPtrArrayIndex = 0;
			for( ; voidPtrArrayIndex < voidPtrArrayCount; ++voidPtrArrayIndex )
				varDirector->release( voidPtrArrayPtr[ voidPtrArrayIndex ] );
			vector->clear( );
			delete vector;
		}
	allVarPtrVector.clear( );

}
NodeTypeInfoPtrArrayStack::NodeTypeInfoPtrArrayStack( ) {

}

bool NodeTypeInfoPtrArrayStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( , std::vector< NodeTypeInfo * >, "vector< NodeTypeInfo * >", "NodeTypeInfo *[]", "NodeTypeInfoPtrArray" );
	return true;
}
bool NodeTypeInfoPtrArrayStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t arrayCount = 0;
	if( infoTool::fillTypeVectorAtVar< uint64_t >( result_count, obj_start_ptr, obj_memory_size, &arrayCount ) == false )
		return false;
	auto offset = obj_start_ptr + result_count;
	auto mod = obj_memory_size - result_count;
	std::vector< t_current_unity_type > buffVar( arrayCount );

	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index, offset = offset + result_count,
		mod = mod - result_count ) {
		NodeTypeInfo *targetVarPtr = *( arrayPtr + index );
		if( varDirector->create( targetVarPtr ) == false || targetVarPtr == nullptr )
			return false;
		arrayPtr[ index ] = targetVarPtr;
		void *targetVoidVarPtr = targetVarPtr;
		if( varDirector->toVar( result_count, offset, mod, targetVoidVarPtr ) == false )
			return false;
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
TypeEnum::Type NodeTypeInfoPtrArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
bool NodeTypeInfoPtrArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	std::vector< t_current_unity_type > *vector = ( std::vector< t_current_unity_type > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	if( infoTool::fillTypeVarAtVector< uint64_t >( &arraySize, buff ) == false )
		return false;

	result_data.append_range( buff );
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index )
		if( varDirector->toVector( *( arrayPtr + index ), buff ) == false )
			return false;
		else
			result_data.append_range( buff );
	return true;
}
