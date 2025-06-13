#include "vectorTypeObject.h"
bool VectorTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	size_t count = vector->size( );
	size_t appendSize = sizeof( size_t );
	auto lastPtr = ISerialize::converQMetaObjectInfoToUInt8Vector( result_data_vector, this, typeNames( ), appendSize );
	size_t resultSize = result_data_vector->size( );
	if( resultSize == 0 )
		return false;
	*( size_t * ) lastPtr = count;
	if( count == 0 )
		return true;
	appendSize = resultSize;
	std_vector< std_vector< uint8_t > > append;
	std_vector< uint8_t > unitySer;
	auto data = vector->data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->serializeToVectorData( &unitySer ) ) {
			append.emplace_back( unitySer );
			resultSize += unitySer.size( );
		} else
			tools::debug::printError( "无法序列化此次对象 = > " + QString( "(0x%1) %" ).arg( QString::number( ( size_t ) ( data + index ), 16 ) ).arg( data[ index ]->toString( ) ) );
	result_data_vector->resize( resultSize );
	lastPtr = unitySer.data( ) + appendSize;

	for( index = 0; index < count; )
		for( auto &vect : append ) {
			for( auto unity : vect ) {
				lastPtr[ index ] = unity;
				++index;
			}
		}
	return true;
}
size_t VectorTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	return 0;
}
