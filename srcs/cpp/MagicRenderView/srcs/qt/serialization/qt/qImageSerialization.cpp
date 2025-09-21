#include "./qImageSerialization.h"
#include <QBuffer>
size_t QImageSerialization::fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	// return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );

	t_current_type *image = var_type->get< t_current_type >( );
	if( image == nullptr || image->isNull( ) == true )
		return 0;

	std_vector< uint8_t > resultBuff;
	std_vector< uint8_t > varBuff;
	serialization.fillBinVector( typeName, varBuff );
	resultBuff.append_range( varBuff );
	QString format = "PNG";
	serialization.fillBinVector( format, varBuff );
	resultBuff.append_range( varBuff );

	QByteArray ba;
	QBuffer buffer( &ba );
	if( buffer.open( QIODevice::WriteOnly ) == false )
		return 0;
	image->save( &buffer, format.toStdString( ).c_str( ) );
	buffer.close( );

	BinGenerate::toBin( ba, varBuff );
	resultBuff.append_range( varBuff );
	serialization.fillBinVector( resultBuff.size( ), varBuff );
	result_bin_data_vector.clear( );
	result_bin_data_vector.append_range( varBuff );
	result_bin_data_vector.append_range( resultBuff );
	return result_bin_data_vector.size( );
}
size_t QImageSerialization::fillObj( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {

	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	QImage *image = var_type->get< t_current_type >( );
	if( image == nullptr )
		return 0;

	size_t needCount;
	size_t count = serialization.fillObjVector( &needCount, source_ptr, source_ptr_count );
	size_t mod = source_ptr_count - count;
	if( needCount > mod )
		return 0;
	auto offsetPtr = source_ptr + count;
	QString getTypeName;
	count = serialization.fillObjVector( &getTypeName, offsetPtr, mod );
	if( getTypeName != typeName )
		return 0;
	offsetPtr += count;
	mod -= count;
	// 获取格式类型
	count = serialization.fillObjVector( &getTypeName, offsetPtr, mod );
	offsetPtr += count;
	mod -= count;
	QByteArray ba;
	count = BinGenerate::toObj( &ba, offsetPtr, mod );
	image->loadFromData( ba, getTypeName.toStdString( ).c_str( ) );
	offsetPtr += count;
	return offsetPtr - source_ptr;
}
size_t QImageSerialization::fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t QImageSerialization::fillObj( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
size_t QImageSerialization::fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t QImageSerialization::fillObj( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
