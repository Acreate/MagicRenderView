#include "qColorSerialization.h"

size_t QColorSerializtion::fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	auto color = var_type->get< t_current_type >( );
	if( color == nullptr )
		return 0;

	std_vector< uint8_t > resultBuff;
	std_vector< uint8_t > colorBuff;
	std_vector< uint8_t > varBuff;
	std_vector< uint8_t > countBuff;

	serialization.fillBinVector( typeName, varBuff );
	resultBuff.append_range( varBuff );

	auto colorR = color->red( );
	auto colorG = color->green( );
	auto colorB = color->blue( );
	auto colorA = color->alpha( );

	BinGenerate::toBin( colorR, varBuff );
	resultBuff.append_range( countBuff );
	resultBuff.append_range( varBuff );

	BinGenerate::toBin( colorG, varBuff );
	resultBuff.append_range( countBuff );
	resultBuff.append_range( varBuff );

	BinGenerate::toBin( colorB, varBuff );
	resultBuff.append_range( countBuff );
	resultBuff.append_range( varBuff );

	BinGenerate::toBin( colorA, varBuff );
	resultBuff.append_range( countBuff );
	resultBuff.append_range( varBuff );

	serialization.fillBinVector( resultBuff.size( ), countBuff );
	result_bin_data_vector.clear( );
	result_bin_data_vector.append_range( countBuff );
	result_bin_data_vector.append_range( resultBuff );

	return resultBuff.size( );
}
size_t QColorSerializtion::fillObj( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	auto color = var_type->get< t_current_type >( );
	if( color == nullptr )
		return 0;
	size_t needCount;
	size_t count = serialization.fillObjVector( &needCount, source_ptr, source_ptr_count );
	auto mod = source_ptr_count - count;
	if( needCount > mod )
		return 0;
	auto offsetPtr = source_ptr + count;
	QString readTypeName;
	count = serialization.fillObjVector( &readTypeName, offsetPtr, needCount );
	if( typeName != readTypeName )
		return 0;

	offsetPtr += count;
	mod -= count;

	auto red = color->red( );
	decltype(red) green, blue, alpha;

	count = BinGenerate::toObj( &red, offsetPtr, mod );
	offsetPtr += count;
	mod -= count;

	count = BinGenerate::toObj( &green, offsetPtr, mod );
	offsetPtr += count;
	mod -= count;

	count = BinGenerate::toObj( &blue, offsetPtr, mod );
	offsetPtr += count;
	mod -= count;

	count = BinGenerate::toObj( &alpha, offsetPtr, mod );
	offsetPtr += count;

	*color = QColor( red, green, blue, alpha );

	return offsetPtr - source_ptr;
}
size_t QColorSerializtion::fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t QColorSerializtion::fillObj( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
size_t QColorSerializtion::fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t QColorSerializtion::fillObj( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
