#include "stringArrayStack.h"

#include <define/macro.h>
StringArrayStack::~StringArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( std::vector< QString > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
StringArrayStack::StringArrayStack( ) {
	Stack_Type_Name( , std::vector< QString >, "vector<QString>", "QString[]", "QStringArray", "vector<String>", "String[]", "StringArray" );
}

uint64_t StringArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {

	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	uint64_t arrayCount = 0;
	count = fillTypeVectorAtVar< uint64_t >( offset, mod, &arrayCount );
	if( count == 0 )
		return 0;
	offset = offset + count;
	mod = mod - count;
	std::vector< QString > buffVar( arrayCount );

	auto arrayPtr = buffVar.data( );
	for( size_t index = 0; index < arrayCount; ++index ) {
		QString *ptr = arrayPtr + index;
		count = fillTypeVectorAtVar< QString >( offset, mod, ptr );
		if( count == 0 )
			return 0;
		offset = offset + count;
		mod = mod - count;
	}

	auto createPtr = ( std::vector< QString > * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type StringArrayStack::getType( ) {
	return TypeEnum::Type::Array;
}
uint64_t StringArrayStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	std::vector< QString > *vector = ( std::vector< QString > * ) obj_start_ptr;
	uint64_t arraySize = vector->size( );
	count = fillTypeVarAtVector< uint64_t >( &arraySize, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	auto arrayPtr = vector->data( );
	for( size_t index = 0; index < arraySize; ++index ) {
		QString *ptr = arrayPtr + index;
		count = fillTypeVarAtVector< QString >( ptr, buff );
		if( count == 0 )
			return 0;
		result_data.append_range( buff );
	}
	return result_data.size( );
}
