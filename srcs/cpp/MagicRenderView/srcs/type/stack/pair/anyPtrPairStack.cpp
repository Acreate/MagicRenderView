#include "anyPtrPairStack.h"

#include <app/application.h>

#include <director/varDirector.h>

AnyPtrPairStack::~AnyPtrPairStack( ) {

}
bool AnyPtrPairStack::init( ) {
	typeName = "std::pair< void *, void * >";
	aliasTypeNames = std::vector< QString >( { typeid( std::pair< void *, void * > ).name( ), "pair< void *, void * >", "pair" } );
	setNewObjTypeFunction( [] {
		return new std::pair< void *, void * >( nullptr, nullptr );
	} );
	setDeleteObjTypeFunction( [] ( void *delete_obj_ptr ) {
		delete ( std::pair< void *, void * > * ) delete_obj_ptr;
		return true;
	} );
	return true;
}
AnyPtrPairStack::AnyPtrPairStack( ) {
}

uint64_t AnyPtrPairStack::toObj( const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	uint64_t count;
	QString converTypeName;
	count = getDataAtTypeName( obj_start_ptr, obj_memory_size, converTypeName );
	if( count == 0 )
		return 0;
	if( converTypeName != this->typeName )
		return 0;
	auto offset = obj_start_ptr + count;
	auto mod = obj_memory_size - count;
	std::pair< void *, void * > buffVar;
	auto *varDirector = Application::getInstancePtr( )->getVarDirector( );
	count = varDirector->toVar( offset, mod, buffVar.first );
	if( count == 0 )
		return 0;
	offset = offset + count;
	mod = mod - count;
	count = varDirector->toVar( offset, mod, buffVar.second );
	if( count == 0 )
		return 0;
	offset = offset + count;
	auto createPtr = ( std::pair< void *, void * > * ) createTypePtr( );
	*createPtr = buffVar;
	result_obj_ptr = createPtr;
	return offset - obj_start_ptr;
}
TypeEnum::Type AnyPtrPairStack::getType( ) {
	return TypeEnum::Type::Pair;
}
uint64_t AnyPtrPairStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	uint64_t count;
	count = getTypeNameAtData( result_data );
	if( count == 0 )
		return 0;
	auto *varDirector = Application::getInstancePtr( )->getVarDirector( );
	std::pair< void *, void * > *converPtr = ( std::pair< void *, void * > * ) ( obj_start_ptr );
	count = varDirector->toVector( converPtr->first, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	count = varDirector->toVector( converPtr->second, buff );
	if( count == 0 )
		return 0;
	result_data.append_range( buff );
	return result_data.size( );
}
