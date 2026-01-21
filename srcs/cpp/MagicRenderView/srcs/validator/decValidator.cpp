#include "decValidator.h"

bool DecValidator::checkCharValidator( QChar &check_char ) const {
	if( check_char < '0' || check_char > '9' )
		return false;
	return true;
}
