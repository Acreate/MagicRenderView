#include "qColorSerialization.h"

size_t QColorSerializtion::fillUnityBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	ConverPtr( color, var_type, const t_current_type* );
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
size_t QColorSerializtion::fillUnityObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;

	ConverPtr( color, var_type, t_current_type* );
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
size_t QColorSerializtion::fillVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return serialization.fillVectorBin< t_current_type >( this, var_type, result_bin_data_vector );
}
size_t QColorSerializtion::fillVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return serialization.fillVectorObj< t_current_type >( this, var_type, source_ptr, source_ptr_count );
}
size_t QColorSerializtion::fillPtrVectorBin( const void *var_type, std_vector< uint8_t > &result_bin_data_vector ) {
	return serialization.fillPtrVectorBin< t_current_type >( this, var_type, result_bin_data_vector );
}
size_t QColorSerializtion::fillPtrVectorObj( void *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	return serialization.fillPtrVectorObj< t_current_type >( this, var_type, source_ptr, source_ptr_count );
}
bool QColorSerializtion::getNewObj( void **new_set_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) {
	*new_set_ptr = new t_current_type;
	return true;
}
bool QColorSerializtion::removeNewObj( void *new_set_ptr ) {
	delete ( t_current_type * ) new_set_ptr;
	return true;
}
