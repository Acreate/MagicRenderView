#include "./varGenerate.h"

#include "../varType/I_Conver.h"
#include "../varType/baseVarType.h"
class BaseVarType;
std_vector< std_shared_ptr< I_Conver > > VarGenerate::converVector;
void VarGenerate::append( const std_shared_ptr< I_Conver > &new_conver ) {
	converVector.emplace_back( new_conver );
}
bool VarGenerate::conver( BaseVarType *left, const BaseVarType *right ) {
	return conver( &left->getTypeInfo( ), left->getVarPtr( ), &right->getTypeInfo( ), right->getVarPtr( ) );
}
bool VarGenerate::conver( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
	return conver( &left->getTypeInfo( ), left->getVarPtr( ), right_type_info, right );
}
bool VarGenerate::conver( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count == 0 )
		return false;

	auto data = converVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].get( )->fillTarget( left_type_info, left, right_type_info, right ) )
			return true;
	return false;
}
