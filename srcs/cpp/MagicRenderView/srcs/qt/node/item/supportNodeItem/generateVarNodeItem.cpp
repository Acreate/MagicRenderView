#include "generateVarNodeItem.h"
Imp_StaticMetaInfo( GenerateVarNodeItem, QObject::tr( "生成节点" ), QObject::tr( "接口" ) );

size_t GenerateVarNodeItem::loadBinData( const uint8_t *source_data_ptr, const size_t &source_data_count ) {
	return NodeItem::loadBinData( source_data_ptr, source_data_count );
}
size_t GenerateVarNodeItem::toBinData( std_vector< uint8_t > &result_data ) const {
	return NodeItem::toBinData( result_data );
}
