#include "./nodeWidgetSerialization.h"
#include <qt/widgets/mainWidget.h>
NodeWidgetSerialization::NodeWidgetSerialization( ) : BinGenerateItem( ) {
	typeName = typeid( t_current_type ).name( );
}
size_t NodeWidgetSerialization::fillUnityBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {

	if( var_type == nullptr )
		return 0;
	ConverPtr( mainWidget, var_type, t_current_type* );
	// 开始序列化
	std_vector< uint8_t > resultBuff;
	std_vector< uint8_t > varBuff;
	std_vector< uint8_t > listItemBuff;
	serialization.fillBinVector( typeName, varBuff );
	resultBuff.append_range( varBuff );
	resultBuff.append_range( mainWidget->supportBin );

	size_t count = mainWidget->nodeItemList.size( );
	std_vector< NodeItem * > nodeItems( count );
	auto nodeItemPtr = nodeItems.data( );
	auto iterator = mainWidget->nodeItemList.begin( );
	auto end = mainWidget->nodeItemList.end( );
	for( count = 0; iterator != end; ++iterator, ++count )
		nodeItemPtr[ count ] = *iterator;

	BinGenerate::toBin( nodeItems, listItemBuff );
	auto data = listItemBuff.data( );
	resultBuff.append_range( listItemBuff );
	// 停止序列化
	serialization.fillBinVector( resultBuff.size( ), result_bin_data_vector );
	result_bin_data_vector.append_range( resultBuff );
	return result_bin_data_vector.size( );
}
size_t NodeWidgetSerialization::fillUnityObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {

	Fill_Obj_CheckMemoryType( MainWidget*, mainWidget, var_type, source_ptr, source_ptr_count, needCount, count, mod, offsetPtr, typeName, getTypeName, return 0 );

	size_t supporCount = mainWidget->supportBin.size( );
	if( supporCount > mod )
		return 0; // 支持类型的数据长度
	auto compData = mainWidget->supportBin.data( );
	for( needCount = 0; needCount < supporCount; ++needCount )
		if( compData[ needCount ] != offsetPtr[ needCount ] )
			return 0;
	Next_Ptr( offsetPtr, mod, supporCount );

	std_vector< NodeItem * > nodeItems;
	count = BinGenerate::toObj( &nodeItems, offsetPtr, mod );
	if( count == 0 ) // 未足够填充数组
		return 0;
	offsetPtr += count;
	count = nodeItems.size( );
	auto nodeItemPtr = nodeItems.data( );
	// 开始配置节点
	for( needCount = 0; needCount < count; ++needCount )
		if( mainWidget->appendNodeItem( nodeItemPtr[ needCount ] ) == 0 ) {
			// 添加失败，则释放
			for( needCount = 0; needCount < count; ++needCount )
				delete nodeItemPtr[ needCount ];
			nodeItems.clear( );
			offsetPtr = source_ptr;
			break;
		}
	// 停止配置节点
	return offsetPtr - source_ptr;
}
size_t NodeWidgetSerialization::fillVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return 0;
}
size_t NodeWidgetSerialization::fillVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	return 0;
}
size_t NodeWidgetSerialization::fillPtrVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return 0;
}
size_t NodeWidgetSerialization::fillPtrVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	return 0;
}
bool NodeWidgetSerialization::getNewObj( void **new_set_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return false;
}
bool NodeWidgetSerialization::removeNewObj( void *new_set_ptr ) {
	return false;
}
