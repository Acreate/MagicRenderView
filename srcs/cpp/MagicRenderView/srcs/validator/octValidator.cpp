#include "octValidator.h"


bool OctValidator::checkCharValidator( QChar &check_char ) const {
	if( check_char < '0' || check_char > '8' )
		return false;
	return true;
}
