#include "varGenerate.h"

#include <type/infoStack.h>

#include "stack/array/anyArrayStack.h"
#include "stack/array/float32ArrayStack.h"
#include "stack/array/float64ArrayStack.h"
#include "stack/array/int16ArrayStack.h"
#include "stack/array/int32ArrayStack.h"
#include "stack/array/int64ArrayStack.h"
#include "stack/array/int8ArrayStack.h"
#include "stack/array/stringArrayStack.h"
#include "stack/array/uInt16ArrayStack.h"
#include "stack/array/uInt32ArrayStack.h"
#include "stack/array/uInt64ArrayStack.h"
#include "stack/array/uInt8ArrayStack.h"
#include "stack/pair/anyPtrPairStack.h"
#include "stack/unity/float32UnityStack.h"
#include "stack/unity/float64UnityStack.h"
#include "stack/unity/int16UnityStack.h"
#include "stack/unity/int32UnityStack.h"
#include "stack/unity/int64UnityStack.h"
#include "stack/unity/int8UnityStack.h"
#include "stack/unity/stringUnityStack.h"
#include "stack/unity/uInt16UnityStack.h"
#include "stack/unity/uInt32UnityStack.h"
#include "stack/unity/uInt64UnityStack.h"
#include "stack/unity/uInt8UnityStack.h"
#define emplace_back_type( _Type )\
	stacks.emplace_back( new _Type )
VarGenerate::VarGenerate( ) {
	emplace_back_type( UInt8UnityStack );
	emplace_back_type( UInt16UnityStack );
	emplace_back_type( UInt32UnityStack );
	emplace_back_type( UInt64UnityStack );
	emplace_back_type( Int8UnityStack );
	emplace_back_type( Int16UnityStack );
	emplace_back_type( Int32UnityStack );
	emplace_back_type( Int64UnityStack );
	emplace_back_type( Float32UnityStack );
	emplace_back_type( Float64UnityStack );
	emplace_back_type( StringUnityStack );

	emplace_back_type( UInt8ArrayStack );
	emplace_back_type( UInt16ArrayStack );
	emplace_back_type( UInt32ArrayStack );
	emplace_back_type( UInt64ArrayStack );
	emplace_back_type( Int8ArrayStack );
	emplace_back_type( Int16ArrayStack );
	emplace_back_type( Int32ArrayStack );
	emplace_back_type( Int64ArrayStack );
	emplace_back_type( Float32ArrayStack );
	emplace_back_type( Float64ArrayStack );
	emplace_back_type( StringArrayStack );

	emplace_back_type( AnyPtrPairStack );
	emplace_back_type( AnyArrayStack );
}

VarGenerate::~VarGenerate( ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete arrayPtr[ index ];
	stacks.clear( );
}
void * VarGenerate::create( const QString &create_type_name ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->isTypeName( create_type_name ) )
			return arrayPtr[ index ]->createTypePtr( );
	index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->isAliasTypeNames( create_type_name ) )
			return arrayPtr[ index ]->createTypePtr( );
	return nullptr;
}
uint64_t VarGenerate::toVar( const uint8_t *source_ptr, const size_t &source_count, void *&target_var_ptr ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	uint64_t userCount;
	for( ; index < count; ++index )
		if( userCount = arrayPtr[ index ]->toObj( source_ptr, source_count, target_var_ptr ), userCount != 0 )
			return userCount;
	return 0;
}
uint64_t VarGenerate::toVar( const uint8_t *source_ptr, const size_t &source_count, void **target_var_ptr ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	uint64_t userCount;
	for( ; index < count; ++index )
		if( userCount = arrayPtr[ index ]->toObj( source_ptr, source_count, *target_var_ptr ), userCount != 0 )
			return userCount;
	return 0;
}
uint64_t VarGenerate::toVector( const void *ptr, std::vector< uint8_t > &result ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	uint64_t userCount;
	for( ; index < count; ++index )
		if( userCount = arrayPtr[ index ]->toData( ptr, result ), userCount != 0 )
			return userCount;
	return 0;
}
bool VarGenerate::getTypeName( const type_info &type_info_ref, QString &result_type_name ) {
	QString typeInfoName = type_info_ref.name( );
	return getTypeName( typeInfoName, result_type_name );
}
bool VarGenerate::getTypeName( const QString &type_info_ref, QString &result_type_name ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->isTypeName( type_info_ref ) ) {
			result_type_name = arrayPtr[ index ]->getTypeName( );
			return true;
		}
	index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->isAliasTypeNames( type_info_ref ) ) {
			result_type_name = arrayPtr[ index ]->getTypeName( );
			return true;
		}
	return false;
}
bool VarGenerate::getObjPtrType( const void *check_obj_ptr, TypeEnum::Type &result_bool ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->hasVarPtr( check_obj_ptr ) ) {
			result_bool = arrayPtr[ index ]->getType( );
			return true;
		}
	return false;
}

bool VarGenerate::getObjPtrAtTypeName( const void *check_obj_ptr, QString &result_type_name ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->hasVarPtr( check_obj_ptr ) ) {
			result_type_name = arrayPtr[ index ]->getTypeName( );
			return true;
		}
	return false;
}
bool VarGenerate::realease( const void *delete_obj_ptr ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->deleteTypePtr( delete_obj_ptr ) )
			return true;
	return false;
}
