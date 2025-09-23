#include "./I_Var.h"
void * I_Var::data( const I_Type &target_type_info ) {
	if( target_type_info == typeInfo )
		return varPtr;
	return nullptr;
}
I_Var::I_Var( ): typeInfo( typeid( nullptr ) ), varPtr( nullptr ) { }
bool operator==( const I_Var &lhs, const I_Var &rhs ) {
	return lhs.typeInfo == rhs.typeInfo
		&& lhs.varPtr == rhs.varPtr;
}
bool operator!=( const I_Var &lhs, const I_Var &rhs ) { return !( lhs == rhs ); }
