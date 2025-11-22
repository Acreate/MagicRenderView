#include "anyPtrPairStack.h"

AnyPtrPairStack::~AnyPtrPairStack( ) {
	size_t count = allVarPtrVector.size( );
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( nullptr == arrayPtr[ index ] )
			delete ( std::pair< void *, void * > * ) arrayPtr[ index ];
	allVarPtrVector.clear( );
}
AnyPtrPairStack::AnyPtrPairStack( ) {
	typeName = "std::pair< void *, void * >";
	aliasTypeNames = std::vector< QString >( { typeid( std::pair< void *, void * > ).name( ), "pair< void *, void * >", "pair" } );
}
void * AnyPtrPairStack::createTypePtr( ) {
	auto createObjPtr = new std::pair< void *, void * >;
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
bool AnyPtrPairStack::deleteTypePtr( const void *delete_obj_ptr ) {
	size_t count = allVarPtrVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = allVarPtrVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( delete_obj_ptr == arrayPtr[ index ] ) {
			delete ( std::pair< void *, void * > * ) arrayPtr[ index ];
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

uint64_t AnyPtrPairStack::toData( const void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	return 0;
}
uint64_t AnyPtrPairStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, std::vector< void * > &result_data ) {
	return 0;
}
TypeEnum::Type AnyPtrPairStack::getType( ) {
	return TypeEnum::Type::Unity;
}
