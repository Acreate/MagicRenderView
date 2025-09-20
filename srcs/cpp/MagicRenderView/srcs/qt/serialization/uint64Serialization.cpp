#include "./uint64Serialization.h"

size_t Uint64Serialization::fillBin( const Unity *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	auto dataPtr = var_type->getConst< uint64_t >( );
	if( dataPtr == nullptr )
		return 0;

	std_vector< uint8_t > resultBuff;
	std_vector< uint8_t > countBuff;
	std_vector< uint8_t > nameBuff;
	size_t count = serialization.fillBinVector( typeName, nameBuff );
	serialization.fillBinVector( count, countBuff );
	resultBuff.append_range( countBuff );
	resultBuff.append_range( nameBuff );

	count = serialization.fillBinVector( *dataPtr, nameBuff );
	serialization.fillBinVector( count, countBuff );
	resultBuff.append_range( countBuff );
	resultBuff.append_range( nameBuff );

	count = resultBuff.size( );
	serialization.fillBinVector( count, countBuff );
	result_bin_data_vector.clear( );
	result_bin_data_vector.append_range( countBuff );
	result_bin_data_vector.append_range( resultBuff );
	return result_bin_data_vector.size( );
}
size_t Uint64Serialization::fillObj( Unity *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	auto dataPtr = target_var_ptr->get< uint64_t >( );
	if( dataPtr == nullptr )
		return 0;
	size_t menorySize;
	size_t count = serialization.fillObjVector( &menorySize, source_ptr, source_ptr_count );
	// 获取剩余
	auto mod = source_ptr_count - count;
	if( mod < menorySize )
		return 0;
	auto offset = source_ptr + count;
	QString converTypeName; // 内存当中的类型名称
	count = serialization.fillObjVector( &converTypeName, offset, mod );
	if( converTypeName != typeName ) // 名称不一致
		return 0;
	mod -= count;
	offset += count;
	count = serialization.fillObjVector( &menorySize, offset, mod );
	mod -= count;
	offset += count;
	count = serialization.fillObjVector( dataPtr, offset, mod );
	return offset - source_ptr + count;
}
size_t Uint64Serialization::fillBin( const UnityVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	const std_vector< uint64_t > *dataPtr = var_type->getConst< uint64_t >( );
	if( dataPtr == nullptr )
		return 0;

	std_vector< uint8_t > resultBuff;
	std_vector< uint8_t > countBuff;
	std_vector< uint8_t > nameBuff;
	size_t count = serialization.fillBinVector( typeName, nameBuff );
	serialization.fillBinVector( count, countBuff );
	resultBuff.append_range( countBuff );
	resultBuff.append_range( nameBuff );
	count = dataPtr->size( );
	serialization.fillBinVector( count, countBuff );
	resultBuff.append_range( countBuff );
	size_t index = 0;
	const uint64_t *data = dataPtr->data( );
	for( ; index < count; ++index ) {
		Unity unity;
		unity.init( data[ index ] );
		this->fillBin( &unity, nameBuff );
		resultBuff.append_range( nameBuff );
	}
	count = resultBuff.size( );
	serialization.fillBinVector( count, countBuff );
	result_bin_data_vector.clear( );
	result_bin_data_vector.append_range( countBuff );
	result_bin_data_vector.append_range( resultBuff );
	return 0;
}
size_t Uint64Serialization::fillObj( UnityVector *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	std_vector< uint64_t > *dataPtr = target_var_ptr->get< uint64_t >( );
	if( dataPtr == nullptr )
		return 0;

	size_t menorySize;
	size_t count = serialization.fillObjVector( &menorySize, source_ptr, source_ptr_count );
	// 获取剩余
	auto mod = source_ptr_count - count;
	if( mod < menorySize )
		return 0;
	auto offset = source_ptr + count;
	QString converTypeName; // 内存当中的类型名称
	count = serialization.fillObjVector( &converTypeName, offset, mod );
	if( converTypeName != typeName ) // 名称不一致
		return 0;

	mod -= count;
	offset += count;
	size_t vectorCount;
	count = serialization.fillObjVector( &vectorCount, offset, mod );
	mod -= count;
	offset += count;

	dataPtr->resize( vectorCount );
	uint64_t *data = dataPtr->data( );
	size_t index = 0;
	for( ; index < vectorCount; ++index ) {
		uint64_t var;
		count = serialization.fillObjVector( &var, offset, mod );
		mod -= count;
		offset += count;
		data[ index ] = var;
	}

	return offset - source_ptr;
}
size_t Uint64Serialization::fillBin( const UnityPtrVector *var_type, std_vector< uint8_t > &result_bin_data_vector ) const {
	const std_vector< uint64_t * > *dataPtr = var_type->getConst< uint64_t >( );
	if( dataPtr == nullptr )
		return 0;

	std_vector< uint8_t > resultBuff;
	std_vector< uint8_t > countBuff;
	std_vector< uint8_t > nameBuff;
	size_t count = serialization.fillBinVector( typeName, nameBuff );
	serialization.fillBinVector( count, countBuff );
	resultBuff.append_range( countBuff );
	resultBuff.append_range( nameBuff );
	count = dataPtr->size( );
	serialization.fillBinVector( count, countBuff );
	resultBuff.append_range( countBuff );
	size_t index = 0;
	uint64_t *const*data = dataPtr->data( );
	for( ; index < count; ++index ) {
		Unity unity;
		unity.init( *data[ index ] );
		this->fillBin( &unity, nameBuff );
		resultBuff.append_range( nameBuff );
	}
	count = resultBuff.size( );
	serialization.fillBinVector( count, countBuff );
	result_bin_data_vector.clear( );
	result_bin_data_vector.append_range( countBuff );
	result_bin_data_vector.append_range( resultBuff );
	return 0;

}
size_t Uint64Serialization::fillObj( UnityPtrVector *target_var_ptr, const uint8_t *source_ptr, const size_t &source_ptr_count ) const {
	std_vector< uint64_t * > *dataPtr = target_var_ptr->get< uint64_t >( );
	if( dataPtr == nullptr )
		return 0;

	size_t menorySize;
	size_t count = serialization.fillObjVector( &menorySize, source_ptr, source_ptr_count );
	// 获取剩余
	auto mod = source_ptr_count - count;
	if( mod < menorySize )
		return 0;
	auto offset = source_ptr + count;
	QString converTypeName; // 内存当中的类型名称
	count = serialization.fillObjVector( &converTypeName, offset, mod );
	if( converTypeName != typeName ) // 名称不一致
		return 0;

	mod -= count;
	offset += count;
	size_t vectorCount;
	count = serialization.fillObjVector( &vectorCount, offset, mod );
	mod -= count;
	offset += count;

	size_t index = 0;
	count = dataPtr->size( );
	uint64_t **data = dataPtr->data( );
	for( ; index < count; ++index )
		delete data[ index ];

	dataPtr->resize( vectorCount );
	data = dataPtr->data( );
	for( ; index < vectorCount; ++index ) {
		uint64_t *var = new uint64_t;
		count = serialization.fillObjVector( var, offset, mod );
		mod -= count;
		offset += count;
		data[ index ] = var;
	}

	return offset - source_ptr;
	return 0;
}
