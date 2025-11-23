#include "uInt8UnityStack.h"

#include <define/macro.h>
UInt8UnityStack::~UInt8UnityStack( ) {

}
UInt8UnityStack::UInt8UnityStack( ) {
	Stack_Type_Name( 0, uint8_t, "uint8", "unsigned char" );

	setNewObjTypeFunction( [] {
		return new uint64_t;
	} );
	setDeleteObjTypeFunction( [] ( void *delete_obj_ptr ) {
		delete ( uint64_t * ) delete_obj_ptr;
		return true;
	} );
}

uint64_t UInt8UnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	uint8_t buffVar;
	count = fillTypeVectorAtVar< uint8_t >( offset, mod, &buffVar );
	if( count == 0 )
		return 0;
	offset = offset + count;
	auto createPtr = ( uint8_t * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type UInt8UnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
uint64_t UInt8UnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	count = fillTypeVarAtVector< uint8_t >( obj_start_ptr, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
