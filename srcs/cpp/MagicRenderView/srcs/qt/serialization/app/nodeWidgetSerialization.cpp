#include "./nodeWidgetSerialization.h"
#include <qt/widgets/mainWidget.h>
NodeWidgetSerialization::NodeWidgetSerialization( ) : BinGenerateItem( ) {
	typeName = typeid( t_current_type ).name( );
}
size_t NodeWidgetSerialization::fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {

	auto mainWidget = var_type->get< t_current_type >( );
	if( mainWidget == nullptr )
		return 0;
	// 开始序列化
	mainWidget->isSerialization = true;
	std_vector< uint8_t > resultBuff;
	std_vector< uint8_t > varBuff;
	std_vector< uint8_t > listItemBuff;
	serialization.fillBinVector( typeName, varBuff );
	resultBuff.append_range( varBuff );

	size_t count = mainWidget->nodeItemList.size( );
	std_vector< NodeItem * > nodeItems( count );
	auto nodeItemPtr = nodeItems.data( );
	auto iterator = mainWidget->nodeItemList.begin( );
	auto end = mainWidget->nodeItemList.end( );
	for( count = 0; iterator != end; ++iterator, ++count )
		nodeItemPtr[ count ] = *iterator;
	BinGenerate::toBin( nodeItems, listItemBuff );
	resultBuff.append_range( listItemBuff );
	// 停止序列化
	mainWidget->isSerialization = false;
	result_bin_data_vector.clear( );
	serialization.fillBinVector( resultBuff.size( ), varBuff );
	result_bin_data_vector.append_range( varBuff );
	result_bin_data_vector.append_range( resultBuff );
	return 0;
}
size_t NodeWidgetSerialization::fillObj( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	auto mainWidget = var_type->get< t_current_type >( );
	if( mainWidget == nullptr )
		return 0;

	size_t needCount;
	size_t count = serialization.fillObjVector( &needCount, source_ptr, source_ptr_count );
	size_t mod = source_ptr_count - count;
	if( needCount > mod )
		return 0;
	auto offsetPtr = source_ptr - count;

	QString getTypeName;
	count = serialization.fillObjVector( &getTypeName, offsetPtr, mod );
	if( getTypeName != typeName )
		return 0;
	offsetPtr += count;
	mod -= count;
	std_vector< NodeItem * > nodeItems;
	count = BinGenerate::toObj( &nodeItems, offsetPtr, mod );
	if( count == 0 ) // 未足够填充数组
		return 0;
	offsetPtr += count;
	count = nodeItems.size( );
	auto nodeItemPtr = nodeItems.data( );
	// 开始配置节点
	mainWidget->isSerialization = true;
	for( needCount = 0; needCount < count; ++needCount )
		if( mainWidget->appendNodeItem( nodeItemPtr[ needCount ] ) == 0 ) {
			// 添加失败，则释放
			for( needCount = 0; needCount < count; ++needCount )
				delete nodeItemPtr[ needCount ];
			offsetPtr = source_ptr;
			break;
		}
	// 停止配置节点
	mainWidget->isSerialization = false;
	return offsetPtr - source_ptr;
}
size_t NodeWidgetSerialization::fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return 0;
}
size_t NodeWidgetSerialization::fillObj( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	return 0;
}
size_t NodeWidgetSerialization::fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return 0;
}
size_t NodeWidgetSerialization::fillObj( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	return 0;
}
