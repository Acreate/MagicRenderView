#include "decValidator.h"
DecValidator::DecValidator( QObject *parent ) : QValidator( parent ) {
	maxLen = tr( "%1" ).arg( UINT8_MAX, 0, 10 ).length( );
}
QValidator::State DecValidator::validate( QString &input, int &pos ) const {
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
	return Invalid;
}
