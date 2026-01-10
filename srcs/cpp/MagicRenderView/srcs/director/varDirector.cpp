#include "varDirector.h"

#include <app/application.h>
#include <director/printerDirector.h>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>
#include <type/infoStack.h>

#include "../type/stack/any/arrayPtr/anyPtrArrayStack.h"
#include "../type/stack/any/pairPtr/anyPtrPairStack.h"
#include "../type/stack/any/unity/anyPtrStack.h"
#include "../type/stack/base/array/float32ArrayStack.h"
#include "../type/stack/base/array/float64ArrayStack.h"
#include "../type/stack/base/array/int16ArrayStack.h"
#include "../type/stack/base/array/int32ArrayStack.h"
#include "../type/stack/base/array/int64ArrayStack.h"
#include "../type/stack/base/array/int8ArrayStack.h"
#include "../type/stack/base/array/uInt16ArrayStack.h"
#include "../type/stack/base/array/uInt32ArrayStack.h"
#include "../type/stack/base/array/uInt64ArrayStack.h"
#include "../type/stack/base/array/uInt8ArrayStack.h"
#include "../type/stack/base/unity/float32UnityStack.h"
#include "../type/stack/base/unity/float64UnityStack.h"
#include "../type/stack/base/unity/int16UnityStack.h"
#include "../type/stack/base/unity/int32UnityStack.h"
#include "../type/stack/base/unity/int64UnityStack.h"
#include "../type/stack/base/unity/int8UnityStack.h"
#include "../type/stack/base/unity/uInt16UnityStack.h"
#include "../type/stack/base/unity/uInt32UnityStack.h"
#include "../type/stack/base/unity/uInt64UnityStack.h"
#include "../type/stack/base/unity/uInt8UnityStack.h"
#include "../type/stack/extend/char/arrayPtr/charArrayStack.h"
#include "../type/stack/extend/char/unity/charUnityStack.h"
#include "../type/stack/extend/color/arrayPtr/colorArrayStack.h"
#include "../type/stack/extend/color/unity/colorUnityStack.h"
#include "../type/stack/extend/image/arrayPtr/imageArrayStack.h"
#include "../type/stack/extend/image/unity/imageUnityStack.h"
#include "../type/stack/extend/nodeInfoType/arrayPtr/nodeTypeInfoPtrArrayStack.h"
#include "../type/stack/extend/nodeInfoType/unity/nodeTypeInfoStack.h"
#include "../type/stack/extend/string/arrayPtr/stringArrayStack.h"
#include "../type/stack/extend/string/unity/stringUnityStack.h"

#define emplace_back_type( _Type )\
	stacks.emplace_back( new _Type )
bool VarDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	printerDirector = instancePtr->getPrinterDirector( );
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

	emplace_back_type( AnyPtrStack );
	emplace_back_type( AnyPtrPairStack );
	emplace_back_type( AnyPtrArrayStack );

	emplace_back_type( CharUnityStack );
	emplace_back_type( CharArrayStack );

	emplace_back_type( StringUnityStack );
	emplace_back_type( StringArrayStack );

	emplace_back_type( ColorUnityStack );
	emplace_back_type( ColorArrayStack );

	emplace_back_type( ImageUnityStack );
	emplace_back_type( ImageArrayStack );

	emplace_back_type( NodeTypeInfoStack );
	emplace_back_type( NodeTypeInfoPtrArrayStack );

	count = stacks.size( );
	arrayPtr = stacks.data( );
	for( index = 0; index < count; ++index )
		if( arrayPtr[ index ]->init( this ) == false ) {
			auto className = arrayPtr[ index ]->metaObject( )->className( );
			QString msg( "[ %1 ]变量堆栈类初始化失败" );
			printerDirector->error( msg.arg( className ), Create_SrackInfo( ) );
			for( index = 0; index < count; ++index )
				delete arrayPtr[ index ];
			stacks.clear( );
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
		arrayPtr[ index ]->init( this );
	for( ; index < count; ++index )
		delete arrayPtr[ index ];
	stacks.clear( );
}
bool VarDirector::create( const QString &create_type_name, void *&result_create_obj_ptr ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->isTypeName( create_type_name ) )
			return arrayPtr[ index ]->createTypePtr( result_create_obj_ptr );
	index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->isAliasTypeNames( create_type_name ) )
			return arrayPtr[ index ]->createTypePtr( result_create_obj_ptr );
	return false;
}

bool VarDirector::toVar( size_t &result_count, const uint8_t *source_ptr, const size_t &source_count, void *&target_var_ptr ) {
	if( source_ptr == nullptr || source_count == 0 )
		return false;
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	QString converTypeName;
	const uint8_t *offset;
	size_t mod;
	if( infoTool::fillTypeVectorAtVar< QString >( result_count, source_ptr, source_count, &converTypeName ) == false )
		return false;
	for( ; index < count; ++index ) {
		if( converTypeName != arrayPtr[ index ]->typeName )
			continue;
		offset = source_ptr + result_count;
		mod = source_count - result_count;
		if( arrayPtr[ index ]->toObj( result_count, offset, mod, target_var_ptr ) == false )
			break;
		offset = offset + result_count;
		result_count = offset - source_ptr;
		return true;
	}
	return false;
}
bool VarDirector::toVector( const void *ptr, std::vector< uint8_t > &result ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->toData( ptr, result ) )
			return true;
	return false;
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
bool VarDirector::release( const void *delete_obj_ptr ) {
	size_t count = stacks.size( );
	auto arrayPtr = stacks.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ] && arrayPtr[ index ]->deleteTypePtr( delete_obj_ptr ) )
			return true;
	return false;
}
