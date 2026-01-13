#include "anyPtrStack.h"

#include <app/application.h>

#include <director/varDirector.h>

using t_current_unity_type = void *;
AnyPtrStack::~AnyPtrStack( ) {

}
bool AnyPtrStack::init( VarDirector *var_director ) {
	if( InfoStack::init( var_director ) == false )
		return false;
	typeName = "void *";
	aliasTypeNames = std::vector< QString >( { typeid( t_current_unity_type ).name( ), tr( "anyPtr" ) } );
	setNewObjTypeFunction( [] {
		return nullptr;
	} );
	setDeleteObjTypeFunction( [this] ( void *delete_obj_ptr ) {
		return false;
	} );
	return true;
}
AnyPtrStack::AnyPtrStack( ) {
}

bool AnyPtrStack::toObj( uint64_t &result_count, const uint8_t *obj_start_ptr, const size_t &obj_memory_size, void *&result_obj_ptr ) {
	return false;
}
TypeEnum::Type AnyPtrStack::getType( ) {
	return TypeEnum::Type::Unity;
}
bool AnyPtrStack::toVectorData( void *obj_start_ptr, std::vector< uint8_t > &result_data ) {
	std::vector< uint8_t > buff;
	return false;
}
