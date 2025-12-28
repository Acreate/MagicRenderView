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

using t_current_unity_type = std::pair< void *, void * >;
bool AnyPtrPairStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	t_current_unity_type buffVar( nullptr, nullptr );
	auto *varDirector = Application::getInstancePtr( )->getVarDirector( );
	if( varDirector->toVar( result_count, obj_start_ptr, obj_memory_size, buffVar.first ) == false )
		return false;
	auto offset = obj_start_ptr + result_count;
	auto mod = obj_memory_size - result_count;
	if( varDirector->toVar( result_count, offset, mod, buffVar.second ) == false )
		return false;
	offset = offset + result_count;

	result_count = offset - obj_start_ptr;
	if( hasVarPtr( result_obj_ptr ) == false ) {
		void *sourcePtr = nullptr;
		if( createTypePtr( sourcePtr ) == false )
			return false;
		auto createPtr = ( t_current_unity_type * ) sourcePtr;
		*createPtr = buffVar;
		result_obj_ptr = createPtr;
		return true;
	}

	auto createPtr = ( t_current_unity_type * ) result_obj_ptr;
	*createPtr = buffVar;

	result_count = offset - obj_start_ptr;
	return true;
}
TypeEnum::Type AnyPtrPairStack::getType( ) {
	return TypeEnum::Type::Pair;
}
bool AnyPtrPairStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	auto *varDirector = Application::getInstancePtr( )->getVarDirector( );
	t_current_unity_type *converPtr = ( t_current_unity_type * ) ( obj_start_ptr );
	if( varDirector->toVector( converPtr->first, result_data ) == false )
		return false;
	if( varDirector->toVector( converPtr->second, buff ) == false )
		return false;
	result_data.append_range( buff );
	return true;
}
