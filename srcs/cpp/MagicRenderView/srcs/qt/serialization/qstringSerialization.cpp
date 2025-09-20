#include "./qstringSerialization.h"
QStringSerialization::QStringSerialization( ) : BinGenerateItem( ) {
	typeName = typeid( QString ).name( );
}
size_t QStringSerialization::fillBinVector( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {

	return BinGenerateItem::fillBinVector( *( const QString * ) var_type, result_bin_data_vector );
}
size_t QStringSerialization::fillObjVector( void *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	return BinGenerateItem::fillObjVector( ( QString * ) target_var_ptr, source_ptr, source_ptr_count );
}
