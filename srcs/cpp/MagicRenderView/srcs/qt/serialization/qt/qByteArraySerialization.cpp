#include "qByteArraySerialization.h"
QByteArraySerialization::QByteArraySerialization( ) : BinGenerateItem( ) {
	typeName = typeid( t_current_type ).name( );
}
size_t QByteArraySerialization::fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {

	auto byteArray = var_type->get< t_current_type >( );
	if( byteArray == nullptr )
		return 0;
	std_vector< uint8_t > resultBuff;
	
	std_vector< uint8_t > varBuff;
	serialization.fillBinVector( typeName, varBuff );
	resultBuff.append_range( varBuff );
	
	qint64 varTypeCount = byteArray->size( ), index = 0;
	serialization.fillBinVector( varTypeCount, varBuff );
	resultBuff.append_range( varBuff );
	
	varBuff.resize( varTypeCount );
	auto targetPtr = varBuff.data( );
	auto sourcePtr = byteArray->data( );
	for( ; index < varTypeCount; ++index )
		targetPtr[ index ] = sourcePtr[ index ];
	resultBuff.append_range( varBuff );
	
	serialization.fillBinVector( resultBuff.size( ), varBuff );
	result_bin_data_vector.clear( );
	result_bin_data_vector.append_range( varBuff );
	result_bin_data_vector.append_range( resultBuff );
	return result_bin_data_vector.size( );
}
size_t QByteArraySerialization::fillObj( Unity *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	auto byteArray = var_type->get< t_current_type >( );
	if( byteArray == nullptr )
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
	auto arrayCount = byteArray->size( );
	count = serialization.fillObjVector( &arrayCount, offsetPtr, mod );
	offsetPtr += count;
	mod -= count;
	decltype(arrayCount) index = 0;
	byteArray->resize( arrayCount );
	auto targetPtr = byteArray->data( );
	for( ; index < arrayCount; ++index )
		targetPtr[ index ] = offsetPtr[ index ];
	offsetPtr += arrayCount;
	return offsetPtr - source_ptr;
}
size_t QByteArraySerialization::fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t QByteArraySerialization::fillObj( UnityVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
size_t QByteArraySerialization::fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	return fillBinTemplate< t_current_type >( var_type, result_bin_data_vector );
}
size_t QByteArraySerialization::fillObj( UnityPtrVector *var_type, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	if( source_ptr_count == 0 || source_ptr == nullptr )
		return 0;
	return fillObjTemplate< t_current_type >( var_type, source_ptr, source_ptr_count );
}
