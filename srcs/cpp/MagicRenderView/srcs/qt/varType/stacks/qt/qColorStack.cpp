#include "qColorStack.h"

#include <qcolor.h>
QColorStack::QColorStack( ) : I_Stack( typeid( t_current_type ) ) {

}
bool QColorStack::toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const {
	if( target_type_info != stackTypeInfo )
		return false;

	std_vector< uint8_t > buff;
	std_vector< uint8_t > resultBuff;
	QString typeName = target_type_info.name( );
	fillBinVector( typeName, resultBuff );

	t_current_type *serviliaztionPtr = ( QColor * ) target_ptr;
	int red = serviliaztionPtr->red( );
	int green = serviliaztionPtr->green( );
	int blue = serviliaztionPtr->blue( );
	int alpha = serviliaztionPtr->alpha( );

	fillBinVector( &red, sizeof( int ), buff );
	resultBuff.append_range( buff );

	fillBinVector( &green, sizeof( int ), buff );
	resultBuff.append_range( buff );

	fillBinVector( &blue, sizeof( int ), buff );
	resultBuff.append_range( buff );

	fillBinVector( &alpha, sizeof( int ), buff );
	resultBuff.append_range( buff );

	size_t count = resultBuff.size( );
	fillBinVector( &count, sizeof( size_t ), result_vector );
	result_vector.append_range( resultBuff );
	result_count = result_vector.size( );
	return true;
}
bool QColorStack::toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {

	if( target_type_info != stackTypeInfo )
		return false;
	size_t needCount = 0;
	size_t typeUseCount = sizeof( size_t );
	size_t count = fillObjVector( &needCount, typeUseCount, source_data_ptr, source_data_count );
	size_t mod = source_data_count - count;
	if( needCount > mod )
		return false;
	auto offerPtr = source_data_ptr + count;
	QString typeName;
	count = fillObjVector( &typeName, offerPtr, mod );
	if( typeName != stackTypeInfo.name( ) )
		return false;
	offerPtr += count;
	mod -= count;

	t_current_type *serviliaztionPtr = ( QColor * ) target_ptr;
	int colorBuff;
	count = fillObjVector( &colorBuff, sizeof( int ), offerPtr, mod );
	if( count == 0 )
		return false;
	serviliaztionPtr->setRed( colorBuff );

	offerPtr += count;
	mod -= count;
	count = fillObjVector( &colorBuff, sizeof( int ), offerPtr, mod );
	if( count == 0 )
		return false;
	serviliaztionPtr->setGreen( colorBuff );

	offerPtr += count;
	mod -= count;
	count = fillObjVector( &colorBuff, sizeof( int ), offerPtr, mod );
	if( count == 0 )
		return false;
	serviliaztionPtr->setBlue( colorBuff );

	offerPtr += count;
	mod -= count;
	count = fillObjVector( &colorBuff, sizeof( int ), offerPtr, mod );
	if( count == 0 )
		return false;
	serviliaztionPtr->setAlpha( colorBuff );
	result_count = offerPtr - source_data_ptr;
	return true;
}
