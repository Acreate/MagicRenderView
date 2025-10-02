#include "I_Stack.h"

#include "I_Var.h"

#include "../application/application.h"

#include "../node/item/nodeItem.h"
I_Stack::I_Stack( const type_info &generate_type_info ) : I_Stack( generate_type_info, nullptr, nullptr ) {
}
I_Stack::I_Stack( const type_info &generate_type_info, const std_function< bool( void * ) > &delete_function, const std_function< void *( ) > &create_function ) : generateTypeInfo( generate_type_info ), stackVarPtr( new std_vector< void * > ), childDeleteFunction( delete_function ), childcreateFunction( create_function ) {

	createFunction = [this] {
		auto p = childcreateFunction( );
		if( p != nullptr )
			stackVarPtr->emplace_back( p );
		return p;
	};
	deleteFunction = [this] ( void *target_ptr ) {
		size_t count = stackVarPtr->size( );
		if( count == 0 )
			return false;
		auto data = stackVarPtr->data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ] == target_ptr ) {
				if( childDeleteFunction( data[ index ] ) == false )
					return false;
				stackVarPtr->erase( stackVarPtr->begin( ) + index );
				return true;
			}
		return false;
	};

}
bool I_Stack::getPtrTypeInfo( const void *check_var_ptr, const type_info *&result_type ) const {
	size_t count = stackVarPtr->size( );
	if( count == 0 )
		return false;
	auto data = stackVarPtr->data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] == check_var_ptr ) {
			result_type = &generateTypeInfo;
			return true;
		}
	return false;
}
size_t I_Stack::fillBinVector( const void *source_data_ptr, const size_t &source_ptr_count, std_vector< uint8_t > &result_mirror_image_bin_vector ) const {
	result_mirror_image_bin_vector.resize( source_ptr_count );
	auto pasteTargetDataPtr = result_mirror_image_bin_vector.data( );
	auto copyTargetDataPtr = ( const uint8_t * ) source_data_ptr;
	for( size_t index = 0; index < source_ptr_count; ++index )
		pasteTargetDataPtr[ index ] = copyTargetDataPtr[ index ];
	return source_ptr_count;
}
size_t I_Stack::fillBinVector( const QString &var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	std_vector< uint8_t > buff;
	auto byteArray = var_type.toUtf8( );
	fillBinVector( byteArray.data( ), byteArray.size( ), buff );
	size_t buffCount = buff.size( );
	fillBinVector( &buffCount, sizeof( size_t ), result_bin_data_vector );
	result_bin_data_vector.append_range( buff );
	return result_bin_data_vector.size( );
}
size_t I_Stack::fillObjVector( void *target_var_ptr, const size_t &target_need_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
	if( target_need_count > source_data_count )
		return 0;
	memcpy( target_var_ptr, source_data_ptr, target_need_count );
	return target_need_count;
}
size_t I_Stack::fillObjVector( QString *target_var_ptr, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
	size_t count;
	auto add = fillObjVector( &count, sizeof( size_t ), source_data_ptr, source_data_count );
	if( count > ( source_data_count - add ) )
		return 0;
	const char *sourcePtr = ( const char * ) source_data_ptr + add;
	QByteArray array( sourcePtr, count );
	*target_var_ptr = QString::fromUtf8( array );
	return count + add;
}

void I_Stack::setIVarGenerateCode( I_Var *var, const size_t &new_var_generate_code ) const {
	var->generateCode = new_var_generate_code;
}
void I_Stack::setIVarVarName( I_Var *var, const QString &new_var_name ) const {
	var->varName = new_var_name;
}
const std_vector< I_Var * > & I_Stack::getNodeItemVars( const NodeItem *node_item ) const {
	return node_item->varVector;
}
std_vector< I_Var * > & I_Stack::getNodeItemVars( NodeItem *node_item ) const {
	return node_item->varVector;
}
size_t I_Stack::getTypeName( QString &result_type_name, const uint8_t *source_data_ptr, const size_t &source_data_count ) {

	size_t resultCount = *( size_t * ) source_data_ptr;
	size_t typeUseCount = sizeof( size_t ); // 总数量变量占用 
	size_t mod = source_data_count - typeUseCount;
	if( resultCount > mod )
		return 0; // 不足，则返回
	auto offerPtr = source_data_ptr + typeUseCount;
	resultCount = *( size_t * ) offerPtr;// 字符串数量变量占用
	mod = mod - typeUseCount;
	if( resultCount > mod )
		return 0; // 不足，则返回
	offerPtr += typeUseCount;
	QByteArray array( ( const char * ) offerPtr, resultCount );
	result_type_name = QString::fromUtf8( array );
	return offerPtr + typeUseCount - source_data_ptr;
}
