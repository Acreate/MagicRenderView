#include "decValidator.h"

void DecValidator::setMaxValue( uint64_t value ) {
	maxLen = tr( "%1" ).arg( value, 0, 10 ).length( );
}
bool DecValidator::checkCharValidator( QChar &check_char ) const {
	if( check_char < '0' || check_char > '9' )
		return false;
	return true;
}
