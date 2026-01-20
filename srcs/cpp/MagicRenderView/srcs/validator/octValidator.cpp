#include "octValidator.h"

void OctValidator::setMaxValue( uint64_t value ) {
	maxLen = tr( "%1" ).arg( value, 0, 8 ).length( );
}
bool OctValidator::checkCharValidator( QChar &check_char ) const {
	if( check_char < '0' && check_char > '8' )
		return false;
	return true;
}
