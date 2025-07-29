#include "nullTypeObject.h"

#include "qt/stacks/varStack/IVarStack.h"
#include "qt/stacks/varStack/base/baseVarStack.h"
NullTypeObject::NullTypeObject( IVarStack *generate_this_var_stack_ptr_ptr, const std_function< std_shared_ptr< IVarStack >( ) > &gener_var_stack, const std_vector< QString > &alias_type_name, QObject *parent ): ITypeObject( generate_this_var_stack_ptr_ptr, gener_var_stack, alias_type_name, parent ) {
	thisPtr = nullptr;
	if( gener_var_stack == nullptr ) {
		getStackFunction = [] { return IVarStack::getInstance< BaseVarStack >( ); };
		varStackSharedPtr = getStackFunction( );
	}
}
bool NullTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	auto object = metaObject( );
	auto nativeTypeName = typeNames( );
	converQMetaObjectInfoToUInt8Vector( result_data_vector, object, getStackTypeNames( ), nativeTypeName, 0 );
	return result_data_vector->size( );
}
size_t NullTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	std_vector< uint8_t > resultData;
	auto object = metaObject( );
	auto nativeTypeName = typeNames( );
	auto lastDataPtr = converQMetaObjectInfoToUInt8Vector( &resultData, object, getStackTypeNames( ), nativeTypeName, 0 );
	size_t size = resultData.size( );
	if( size > data_count ) {
		tools::debug::printError( "无法满足对象信息序列化校验需求" );
		return false;
	}
	auto resultDataPtr = resultData.data( );
	type_size_t start = 0;
	for( ; ( resultDataPtr + start ) != lastDataPtr; ++start )
		if( resultDataPtr[ start ] != read_data_vector[ start ] ) {
			tools::debug::printError( "类型信息不匹配" );
			return false;
		}
	return size;
}
