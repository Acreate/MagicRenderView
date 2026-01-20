#include "hexValidator.h"

void HexValidator::setMaxValue( uint64_t value ) {
	maxLen = tr( "%1" ).arg( value, 0, 16 ).length( );
}
bool HexValidator::checkCharValidator( QChar &check_char ) const {
	if( check_char < '0' || check_char > '9' ) {
		auto buffChar = check_char.toUpper( );
		if( buffChar < 'A' || buffChar > 'F' )
			return false;
	}
	return true;
}
