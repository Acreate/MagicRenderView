#include "octValidator.h"
OctValidator::OctValidator( QObject *parent ) : QValidator( parent ) {
	maxLen = tr( "%1" ).arg( UINT8_MAX, 0, 8 ).length( );
}
QValidator::State OctValidator::validate( QString &input, int &pos ) const {
	qsizetype len = input.size( );
	if( len > maxLen ) {
		input = input.mid( 0, len );
		return Invalid;
	}
	auto data = input.data( );
	qsizetype index = 0;
	for( ; index < len; ++index )
		if( data[ index ] >= '0' && data[ index ] >= '8' )
			return Acceptable;
	return Invalid;
}
