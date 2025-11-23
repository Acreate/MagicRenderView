#include "varDirector.h"

#include <type/infoStack.h>
#include <type/stack/array/anyArrayStack.h>
#include <type/stack/array/float32ArrayStack.h>
#include <type/stack/array/float64ArrayStack.h>
#include <type/stack/array/int16ArrayStack.h>
#include <type/stack/array/int32ArrayStack.h>
#include <type/stack/array/int64ArrayStack.h>
#include <type/stack/array/int8ArrayStack.h>
#include <type/stack/array/stringArrayStack.h>
#include <type/stack/array/uInt16ArrayStack.h>
#include <type/stack/array/uInt32ArrayStack.h>
#include <type/stack/array/uInt64ArrayStack.h>
#include <type/stack/array/uInt8ArrayStack.h>
#include <type/stack/pair/anyPtrPairStack.h>
#include <type/stack/unity/float32UnityStack.h>
#include <type/stack/unity/float64UnityStack.h>
#include <type/stack/unity/int16UnityStack.h>
#include <type/stack/unity/int32UnityStack.h>
#include <type/stack/unity/int64UnityStack.h>
#include <type/stack/unity/int8UnityStack.h>
#include <type/stack/unity/stringUnityStack.h>
#include <type/stack/unity/uInt16UnityStack.h>
#include <type/stack/unity/uInt32UnityStack.h>
#include <type/stack/unity/uInt64UnityStack.h>
#include <type/stack/unity/uInt8UnityStack.h>

#include "printerDirector.h"

#include "../app/application.h"

#define emplace_back_type( _Type )\
	stacks.emplace_back( new _Type )
bool VarDirector::init( ) {
	size_t count = stacks.size( );
	InfoStack **arrayPtr;
	size_t index;
	if( count != 0 ) {
		arrayPtr = stacks.data( );
		index = 0;
		for( ; index < count; ++index )
			delete arrayPtr[ index ];
		stacks.clear( );
	}

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
	arrayPtr = stacks.data( );
	index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->init( ) == false ) {
			auto className = arrayPtr[ index ]->metaObject( )->className( );
			QString msg( "[ %1 ]堆栈类初始化失败" );
			Application::getInstancePtr( )->getPrinterDirector( )->error( msg.arg( className ) );
			return false;
		}
	return true;
}
VarDirector::VarDirector( ) {

}

VarDirector::~VarDirector( ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete arrayPtr[ index ];
	stacks.clear( );
}
void * VarDirector::create( const QString &create_type_name ) {
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
uint64_t VarDirector::toVar( const uint8_t *source_ptr, const size_t &source_count, void *&target_var_ptr ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	uint64_t userCount;
	for( ; index < count; ++index )
		if( userCount = arrayPtr[ index ]->toObj( source_ptr, source_count, target_var_ptr ), userCount != 0 )
			return userCount;
	return 0;
}
uint64_t VarDirector::toVar( const uint8_t *source_ptr, const size_t &source_count, void **target_var_ptr ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	uint64_t userCount;
	for( ; index < count; ++index )
		if( userCount = arrayPtr[ index ]->toObj( source_ptr, source_count, *target_var_ptr ), userCount != 0 )
			return userCount;
	return 0;
}
uint64_t VarDirector::toVector( const void *ptr, std::vector< uint8_t > &result ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	uint64_t userCount;
	for( ; index < count; ++index )
		if( userCount = arrayPtr[ index ]->toData( ptr, result ), userCount != 0 )
			return userCount;
	return 0;
}
bool VarDirector::getTypeName( const type_info &type_info_ref, QString &result_type_name ) {
	QString typeInfoName = type_info_ref.name( );
	return getTypeName( typeInfoName, result_type_name );
}
bool VarDirector::getTypeName( const QString &type_info_ref, QString &result_type_name ) {
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
bool VarDirector::getObjPtrType( const void *check_obj_ptr, TypeEnum::Type &result_bool ) {
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

bool VarDirector::getObjPtrAtTypeName( const void *check_obj_ptr, QString &result_type_name ) {
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
bool VarDirector::realease( const void *delete_obj_ptr ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->deleteTypePtr( delete_obj_ptr ) )
			return true;
	return false;
}
