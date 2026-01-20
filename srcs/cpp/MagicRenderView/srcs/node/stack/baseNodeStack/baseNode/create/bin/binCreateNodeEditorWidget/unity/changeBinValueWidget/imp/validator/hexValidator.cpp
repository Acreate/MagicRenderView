#include "hexValidator.h"
HexValidator::HexValidator( QObject *parent ) : QValidator( parent ) {
	maxLen = tr( "%1" ).arg( UINT8_MAX, 0, 16 ).length( );
}
QValidator::State HexValidator::validate( QString &input, int &pos ) const {
	qsizetype len = input.size( );
	if( len > maxLen ) {
		input = input.mid( 0, len );
		return Invalid;
	}
	auto data = input.data( );
	qsizetype index = 0;
	for( ; index < len; ++index )
		if( data[ index ] >= '0' && data[ index ] >= '9' )
			return Acceptable;
		else if( data[ index ] >= 'a' && data[ index ] >= 'f' )
			return Acceptable;
		else if( data[ index ] >= 'A' && data[ index ] >= 'F' )
			return Acceptable;
	return Invalid;
}
