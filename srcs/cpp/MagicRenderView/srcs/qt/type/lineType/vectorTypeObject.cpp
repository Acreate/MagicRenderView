#include "vectorTypeObject.h"
bool VectorTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	// 序列化成员对象到数据
	uint8_t *dataPtr;
	uint8_t *targetDataPtr;
	size_t targetIndex = 0;
	size_t copySize;
	size_t copyIndex;

	size_t buffSize = 0;
	size_t thisValVectorIndex = 0;
	std_vector< uint8_t > unityDataVector( buffSize ), serializeBuff;
	size_t thisValVectorCount = vector->size( );
	auto thisValVectorDataPtr = vector->data( );

	for( ; thisValVectorIndex < thisValVectorCount; ++thisValVectorIndex ) {
		if( thisValVectorDataPtr[ thisValVectorIndex ]->serializeToVectorData( &serializeBuff ) == false )
			return false;
		dataPtr = serializeBuff.data( );
		copySize = serializeBuff.size( );
		if( buffSize < copySize ) {
#define extend_size (1024)
			copySize += copySize + extend_size;
			targetIndex = ( size_t ) ( unityDataVector.data( ) - targetIndex );
			unityDataVector.reserve( copySize );
		}
		targetDataPtr = unityDataVector.data( );
		for( copyIndex = 0; thisValVectorIndex < copySize; ++copyIndex, ++targetIndex )
			targetDataPtr[ targetIndex ] = dataPtr[ copyIndex ];
	}
	size_t appendSize = sizeof( size_t );
	auto lastPtr = ISerialize::converQMetaObjectInfoToUInt8Vector( result_data_vector, this, typeNames( ), appendSize );
	size_t resultSize = result_data_vector->size( );
	if( resultSize == 0 )
		return false;
	*( size_t * ) lastPtr = thisValVectorCount;
	if( thisValVectorCount == 0 )
		return true;
	appendSize = resultSize;
	std_vector< std_vector< uint8_t > > append;
	std_vector< uint8_t > unitySer;
	auto data = vector->data( );
	size_t index = 0;
	for( ; index < thisValVectorCount; ++index )
		if( data[ index ]->serializeToVectorData( &unitySer ) ) {
			append.emplace_back( unitySer );
			resultSize += unitySer.size( );
		} else
			tools::debug::printError( "无法序列化此次对象 = > " + QString( "(0x%1) %" ).arg( QString::number( ( size_t ) ( data + index ), 16 ) ).arg( data[ index ]->toString( ) ) );
	result_data_vector->resize( resultSize );
	lastPtr = unitySer.data( ) + appendSize;

	for( index = 0; index < thisValVectorCount; )
		for( auto &vect : append ) {
			for( auto unity : vect ) {
				lastPtr[ index ] = unity;
				++index;
			}
		}
	return true;
}
size_t VectorTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	// 序列化序列成员

	std_vector< uint8_t > result;
	size_t appendSize = sizeof( size_t );

	auto lastPtr = ISerialize::converQMetaObjectInfoToUInt8Vector( &result, this, typeNames( ), appendSize );
	size_t resultSize = result.size( );
	if( resultSize == 0 )
		return false;

	return 0;
}
