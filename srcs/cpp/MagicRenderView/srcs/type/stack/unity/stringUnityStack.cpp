#include "stringUnityStack.h"

#include <define/macro.h>
StringUnityStack::~StringUnityStack( ) {

}
StringUnityStack::StringUnityStack( ) {
	Stack_Type_Name( QString, "string" );
	newObjTypeFunction = [] {
		return new QString;
	};
	deleteObjTypeFunction = [] ( void *delete_obj_ptr ) {
		delete ( QString * ) delete_obj_ptr;
		return true;
	};
}

uint64_t StringUnityStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	QString buffVar;
	count = fillTypeVectorAtVar< QString >( offset, mod, &buffVar );
	if( count == 0 )
		return 0;
	offset = offset + count;
	auto createPtr = ( QString * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type StringUnityStack::getType( ) {
	return TypeEnum::Type::Unity;
}
uint64_t StringUnityStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	count = fillTypeVarAtVector< QString >( obj_start_ptr, buff );
	if( count == 0 ) // 字符串为空时，该返回为 0
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
