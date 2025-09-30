#include "nodeItemTypeSerialization‌.h"

#include "../../application/application.h"

#include "../../generate/varGenerate.h"

#include "../../node/item/nodeItem.h"
NodeItemTypeSerialization‌::NodeItemTypeSerialization‌( ) : I_Serialization‌( typeid( NodeItem ) ) { }
bool NodeItemTypeSerialization‌::checkTypeInfo( const type_info &type_info ) {
	return typeid( NodeItem ).before( type_info ); // 支持 NodeItem 子类
}

bool NodeItemTypeSerialization‌::appendVarType( const I_Type *append_unity ) {

	std_vector< uint8_t > buff;
	size_t result_count;
	bool binVector = varInstance->toBinVector( append_unity->getTypeInfo( ), append_unity->getPtr( ), buff, result_count );
	if( binVector == false )
		return false;
	serializationMap.emplace_back( append_unity, buff );
	return true;
}
bool NodeItemTypeSerialization‌::removeVarType( const I_Type *append_unity ) {

	size_t count = serializationMap.size( );
	if( count == 0 )
		return false;
	auto data = serializationMap.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first == append_unity ) {
			serializationMap.erase( serializationMap.begin( ) + index );
			return true;
		}
	return false;
}
bool NodeItemTypeSerialization‌::get( const size_t &index, const I_Type *&result_unity ) const {
	size_t count = serializationMap.size( );
	if( count == 0 || index >= count )
		return false;
	auto data = serializationMap.data( );
	result_unity = data[ index ].first;
	return true;
}
bool NodeItemTypeSerialization‌::set( const size_t &index, const I_Type *new_unity ) {
	size_t count = serializationMap.size( );
	if( count == 0 || index >= count )
		return false;

	std_vector< uint8_t > buff;
	size_t result_count;
	bool binVector = varInstance->toBinVector( new_unity->getTypeInfo( ), new_unity->getPtr( ), buff, result_count );
	if( binVector == false )
		return false;

	auto data = serializationMap.data( );
	data[ index ].first = new_unity;
	data[ index ].second = buff;
	return true;
}
size_t NodeItemTypeSerialization‌::getBinVector( std_vector< uint8_t > &result_bin ) const {
	size_t count = serializationMap.size( );
	if( count == 0 )
		return 0;

	std_vector< uint8_t > buff;
	size_t result_count;
	bool binVector = varInstance->toBinVector( typeid( size_t ), &count, buff, result_count );
	if( binVector == false )
		return 0;

	auto data = serializationMap.data( );
	for( size_t index = 0; index < count; ++index )
		buff.append_range( data[ index ].second );

	count = buff.size( );
	binVector = varInstance->toBinVector( typeid( size_t ), &count, result_bin, result_count );
	if( binVector == false )
		return 0;
	result_bin.append_range( buff );
	return result_bin.size( );
}
size_t NodeItemTypeSerialization‌::setBinVector( const uint8_t *init_bin_data_ptr, const size_t &init_bin_data_count ) const {

	size_t needCount;
	size_t result_count;

	bool binVector = varInstance->toOBjVector( typeid( size_t ), &needCount, result_count, init_bin_data_ptr, init_bin_data_count );// 需要元素数量
	if( binVector )
		return 0;
	size_t mod = init_bin_data_count - result_count;
	if( needCount > result_count )
		return 0;
	auto offsetPtr = init_bin_data_ptr + result_count;
	binVector = varInstance->toOBjVector( typeid( size_t ), &needCount, result_count, init_bin_data_ptr, init_bin_data_count ); // 数组个数
	if( binVector )
		return 0;
	// todo : 实现类型

	return offsetPtr - init_bin_data_ptr;
}
