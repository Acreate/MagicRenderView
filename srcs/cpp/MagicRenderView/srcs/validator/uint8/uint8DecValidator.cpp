#include "uint8DecValidator.h"

Uint8DecValidator::Uint8DecValidator( QObject *parent ) : Validator( UINT8_MAX, 10, parent ) {
	binSystem = 10;
	maxLen = tr( "%1" ).arg( UINT8_MAX, 0, binSystem ).length( );
}
Uint8DecValidator::~Uint8DecValidator( ) {

}