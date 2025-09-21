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
	serialization.fillBinVector( typeName, varBuff );
	resultBuff.append_range( varBuff );
	

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
	// 开始序列化
	mainWidget->isSerialization = true;

	// 停止序列化
	mainWidget->isSerialization = false;
	return 0;
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
