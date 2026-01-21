#include "uint8OctValidator.h"

Uint8OctValidator::Uint8OctValidator( QObject *parent ) : Validator( UINT8_MAX, 8, parent ) {
	binSystem = 8;
	maxLen = tr( "%1" ).arg( UINT8_MAX, 0, binSystem ).length( );
}
Uint8OctValidator::~Uint8OctValidator( ) {

}
