#include "./varGenerate.h"

#include "../varType/I_Conver.h"
#include "../varType/baseVarType.h"
#include "../varType/I_Type.h"
class BaseVarType;
std_vector< std_shared_ptr< I_Conver > > VarGenerate::converVector;
std_vector< BaseVarType * > VarGenerate::baseVarStack;
std_vector< std_pairt< std_shared_ptr< I_Type >, std_function< BaseVarType*( QObject * ) > > > VarGenerate::varTypeGenerateVector;
void VarGenerate::appendConverInstance( const std_shared_ptr< I_Conver > &new_conver ) {
	converVector.emplace_back( new_conver );
}
void VarGenerate::appendVarTypeGenerateInstance( const std_shared_ptr< I_Type > &info, const std_function< BaseVarType*( QObject * ) > &generate_instance_function ) {
	varTypeGenerateVector.insert( varTypeGenerateVector.begin( ), std_pairt { info, generate_instance_function } );
}

bool VarGenerate::conver( BaseVarType &left, const BaseVarType &right ) {
	return conver( left.typeInfo.get( ), left.getVarPtr( ), right.typeInfo.get( ), right.getVarPtr( ) );
}
bool VarGenerate::conver( BaseVarType *left, const BaseVarType *right ) {
	return conver( left->typeInfo.get( ), left->getVarPtr( ), right->typeInfo.get( ), right->getVarPtr( ) );
}
bool VarGenerate::conver( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
	return conver( left->typeInfo.get( ), left->getVarPtr( ), right_type_info, right );
}

bool VarGenerate::add( BaseVarType &left, const BaseVarType &right ) {
	return add( left.typeInfo.get( ), left.getVarPtr( ), right.typeInfo.get( ), right.getVarPtr( ) );
}
bool VarGenerate::add( BaseVarType *left, const BaseVarType *right ) {
	return add( left->typeInfo.get( ), left->getVarPtr( ), right->typeInfo.get( ), right->getVarPtr( ) );
}
bool VarGenerate::add( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
	return add( left->typeInfo.get( ), left->getVarPtr( ), right_type_info, right );
}


bool VarGenerate::sub( BaseVarType &left, const BaseVarType &right ) {
	return sub( left.typeInfo.get( ), left.getVarPtr( ), right.typeInfo.get( ), right.getVarPtr( ) );
}
bool VarGenerate::sub( BaseVarType *left, const BaseVarType *right ) {
	return sub( left->typeInfo.get( ), left->getVarPtr( ), right->typeInfo.get( ), right->getVarPtr( ) );
}
bool VarGenerate::sub( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
	return sub( left->typeInfo.get( ), left->getVarPtr( ), right_type_info, right );
}

bool VarGenerate::mul( BaseVarType &left, const BaseVarType &right ) {
	return mul( left.typeInfo.get( ), left.getVarPtr( ), right.typeInfo.get( ), right.getVarPtr( ) );
}
bool VarGenerate::mul( BaseVarType *left, const BaseVarType *right ) {
	return mul( left->typeInfo.get( ), left->getVarPtr( ), right->typeInfo.get( ), right->getVarPtr( ) );
}
bool VarGenerate::mul( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
	return mul( left->typeInfo.get( ), left->getVarPtr( ), right_type_info, right );
}

bool VarGenerate::dev( BaseVarType &left, const BaseVarType &right ) {
	return dev( left.typeInfo.get( ), left.getVarPtr( ), right.typeInfo.get( ), right.getVarPtr( ) );
}
bool VarGenerate::dev( BaseVarType *left, const BaseVarType *right ) {
	return dev( left->typeInfo.get( ), left->getVarPtr( ), right->typeInfo.get( ), right->getVarPtr( ) );
}
bool VarGenerate::dev( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
	return dev( left->typeInfo.get( ), left->getVarPtr( ), right_type_info, right );
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
bool VarGenerate::add( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count == 0 )
		return false;

	auto data = converVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].get( )->addTarget( left_type_info, left, right_type_info, right ) )
			return true;
	return false;
}
bool VarGenerate::sub( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count == 0 )
		return false;

	auto data = converVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].get( )->subTarget( left_type_info, left, right_type_info, right ) )
			return true;
	return false;
}
bool VarGenerate::mul( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count == 0 )
		return false;

	auto data = converVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].get( )->mulTarget( left_type_info, left, right_type_info, right ) )
			return true;
	return false;
}
bool VarGenerate::dev( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {
	size_t count = converVector.size( );
	if( count == 0 )
		return false;

	auto data = converVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].get( )->devTarget( left_type_info, left, right_type_info, right ) )
			return true;
	return false;
}
BaseVarType * VarGenerate::createVarType( const I_Type &create_type, QObject *parent ) {
	size_t count = varTypeGenerateVector.size( );
	if( count == 0 )
		return nullptr;
	auto data = varTypeGenerateVector.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		auto &pair = data[ index ];
		I_Type &leftType = *pair.first.get( );
		if( leftType != create_type )
			continue;
		auto sharedPtr = pair.second( parent );
		if( sharedPtr == nullptr )
			continue;
		return sharedPtr;
	}
	return nullptr;
}
BaseVarType * VarGenerate::createVarType( const type_info &create_type, QObject *parent ) {
	return createVarType( I_Type( create_type ), parent );
}
BaseVarType * VarGenerate::createVarType( const type_info &create_type ) {
	return createVarType( create_type, nullptr );
}
std_vector< std_shared_ptr< I_Type > > VarGenerate::getSupporType( ) {
	std_vector< std_shared_ptr< I_Type > > result;
	size_t count = varTypeGenerateVector.size( );
	if( count == 0 )
		return result;
	auto data = varTypeGenerateVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		result.emplace_back( data[ index ].first );
	return result;
}
