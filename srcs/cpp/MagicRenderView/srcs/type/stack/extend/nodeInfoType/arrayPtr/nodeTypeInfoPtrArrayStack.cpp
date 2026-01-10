#include "nodeTypeInfoPtrArrayStack.h"

#include <define/macro.h>
#include <director/varDirector.h>
#include <tools/infoTool.h>

#include <node/nodeType/nodeTypeInfo.h>

#include "../../../../../app/application.h"
#include "../../../../../director/printerDirector.h"
#include "../../../../../srack/srackInfo.h"

using t_current_unity_type = NodeTypeInfo *;
NodeTypeInfoPtrArrayStack::~NodeTypeInfoPtrArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] ) {
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
	size_t count = allVarPtrVector.size( );
	if( count ) {
		if( deleteObjTypeFunctionIsNull( ) ) {
			Application::getInstancePtr( )->getPrinterDirector( )->error( tr( "未初始化创建函数表达式，请初始化 deleteObjTypeFunction 函数指向调用" ), Create_SrackInfo( ) );
			return false;
		}
		auto arrayPtr = allVarPtrVector.data( );
		for( size_t index = 0; index < count; ++index )
			if( arrayPtr[ index ] ) {
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
	if( InfoStack::init( var_director ) == false )
		return false;
	Stack_Type_Name( , std::vector< NodeTypeInfo * >, "vector< NodeTypeInfo * >", "NodeTypeInfo *[]", "NodeTypeInfoPtrArray" );
	return true;
}
bool NodeTypeInfoPtrArrayStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	std::vector< t_current_unity_type > *sourcePtr = nullptr;
	if( hasVarPtr( result_obj_ptr ) == false ) {
		if( varDirector->create( sourcePtr ) == false || sourcePtr == nullptr )
			return false;
		result_obj_ptr = sourcePtr;
		return true;
	} else
		sourcePtr = ( std::vector< t_current_unity_type > * ) result_obj_ptr;

	uint64_t arrayCount = 0;
	if( infoTool::fillTypeVectorAtVar< uint64_t >( result_count, obj_start_ptr, obj_memory_size, &arrayCount ) == false )
		return false;
	auto offset = obj_start_ptr + result_count;
	auto mod = obj_memory_size - result_count;
	std::vector< t_current_unity_type > buffVar( arrayCount );

	auto arrayPtr = buffVar.data( );
	size_t index = 0;
	for( ; index < arrayCount; ++index, offset = offset + result_count,
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
	arrayCount = sourcePtr->size( );
	if( arrayCount != 0 )
		for( arrayPtr = sourcePtr->data( ), index = 0; index < arrayCount; ++index )
			varDirector->release( arrayPtr[ index ] );
	*sourcePtr = buffVar;
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
