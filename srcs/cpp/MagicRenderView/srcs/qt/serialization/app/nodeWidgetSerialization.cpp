#include "./nodeWidgetSerialization.h"
#include <qt/widgets/mainWidget.h>
NodeWidgetSerialization::NodeWidgetSerialization( ): BinGenerateItem( ) {
	typeName = typeid( t_current_type ).name( );
}
size_t NodeWidgetSerialization::fillBin( const Unity *var_type, std_vector<uint8_t> &result_bin_data_vector ) const {



	
	return 0;
}
size_t NodeWidgetSerialization::fillObj( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	return 0;
}
size_t NodeWidgetSerialization::fillBin( const UnityVector *var_type, std_vector<uint8_t> &result_bin_data_vector ) const {
	return 0;
}
size_t NodeWidgetSerialization::fillObj( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	return 0;
}
size_t NodeWidgetSerialization::fillBin( const UnityPtrVector *var_type, std_vector<uint8_t> &result_bin_data_vector ) const {
	return 0;
}
size_t NodeWidgetSerialization::fillObj( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	return 0;
}
