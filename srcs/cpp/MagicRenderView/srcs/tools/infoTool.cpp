#include "infoTool.h"

#include "../director/varDirector.h"
#include "../node/nodeType/nodeTypeInfo.h"


bool infoTool::toString( const QColor *conver_color_ptr, QString &result_string ) {
	if( conver_color_ptr == nullptr )
		return false;
	QChar firtChar = '0';
	result_string = QString( "0x%1%2%3%4" ).arg( conver_color_ptr->red( ), 2, 16, firtChar ).arg( conver_color_ptr->green( ), 2, 16, firtChar ).arg( conver_color_ptr->blue( ), 2, 16, firtChar ).arg( conver_color_ptr->alpha( ), 2, 16, firtChar ).toUpper( );
	return true;
}
bool infoTool::fillVectorTarget( const uint8_t *ptr, const size_t &ptr_size, std::vector< uint8_t > &result ) {
	result.resize( ptr_size );
	auto data = result.data( );
	for( size_t index = 0; index < ptr_size; ++index )
		data[ index ] = ptr[ index ];
	return true;
}
bool infoTool::fillObjTarget( uint64_t &result_count, const uint8_t *source_ptr, const size_t &source_count, uint8_t *target_var_ptr, const size_t &target_var_count ) {
	if( source_count < target_var_count )
		return false;
	for( size_t index = 0; index < target_var_count; ++index )
		target_var_ptr[ index ] = source_ptr[ index ];
	result_count = target_var_count;
	return true;
}
