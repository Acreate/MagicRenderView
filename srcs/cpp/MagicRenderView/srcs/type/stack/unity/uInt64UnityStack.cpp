#include "uInt64UnityStack.h"

#include <define/macro.h>
UInt64UnityStack::~UInt64UnityStack( ) {

}
UInt64UnityStack::UInt64UnityStack( ) {
	Stack_Type_Name( uint64_t, "uint64", "unsigned long long" );
	newObjTypeFunction = [] {
		return new uint64_t;
	};
	deleteObjTypeFunction = [] ( void *delete_obj_ptr ) {
		delete ( uint64_t * ) delete_obj_ptr;
		return true;
	};
}

uint64_t UInt64UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	uint64_t buffVar;
	count = fillTypeVectorAtVar< uint64_t >( offset, mod, &buffVar );
	if( count == 0 )
		return 0;
	offset = offset + count;
	auto createPtr = ( uint64_t * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type UInt64UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
uint64_t UInt64UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	count = fillTypeVarAtVector< uint64_t >( obj_start_ptr, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
