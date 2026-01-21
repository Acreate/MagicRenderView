#include "binValidator.h"


bool BinValidator::checkCharValidator( QChar &check_char ) const {
	if( check_char != '0' && check_char != '1' )
		return false;
	return true;
}
