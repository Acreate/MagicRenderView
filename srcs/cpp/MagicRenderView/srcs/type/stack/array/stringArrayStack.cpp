#include "stringArrayStack.h"

StringArrayStack::~StringArrayStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( std::vector< QString > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
StringArrayStack::StringArrayStack( ) {
	Stack_Type_Name( std::vector< QString >, "vector<QString>", "QString[]", "QStringArray", "vector<String>", "String[]", "StringArray" );
}
void * StringArrayStack::createTypePtr( ) {
	auto createObjPtr = new std::vector< QString >;
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] ) {
			arrayPtr[ index ] = createObjPtr;
			return createObjPtr;
		}
	allVarPtrVector.emplace_back( createObjPtr );
	return createObjPtr;
}
bool StringArrayStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( std::vector< QString > * ) arrayPtr[ index ];
			count -= 1;
			for( ; index < count; --count )
				if( nullptr == arrayPtr[ count ] ) {
					arrayPtr[ index ] = arrayPtr[ count ];
					return true;
				}
			return true;
		}
	return false;
}

uint64_t StringArrayStack::toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return 0;
}
uint64_t StringArrayStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) {
	return 0;
}
TypeEnum::Type StringArrayStack::getType( ) {
	return TypeEnum::Type::Unity;
}
