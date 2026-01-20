#include "binValidator.h"

void BinValidator::setMaxValue( uint64_t value ) {
	maxLen = tr( "%1" ).arg( value, 0, 2 ).length( );
}
bool BinValidator::checkCharValidator( QChar &check_char ) const {
	if( check_char != '0' && check_char != '1' )
		return false;
	return true;
}
