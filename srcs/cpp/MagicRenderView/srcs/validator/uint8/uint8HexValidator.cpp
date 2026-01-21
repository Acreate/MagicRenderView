#include "uint8HexValidator.h"

Uint8HexValidator::Uint8HexValidator( QObject *parent ) : Validator( UINT8_MAX, 16, parent ) {
	binSystem = 16;
	maxLen = tr( "%1" ).arg( UINT8_MAX, 0, binSystem ).length( );
}
Uint8HexValidator::~Uint8HexValidator( ) {

}
