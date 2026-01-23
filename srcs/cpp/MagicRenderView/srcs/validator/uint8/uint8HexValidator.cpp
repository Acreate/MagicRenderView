#include "uint8HexValidator.h"

Uint8HexValidator::Uint8HexValidator( QObject *parent ) : UnSignedValidator( UINT8_MAX, 0, 16, parent ) {
}
Uint8HexValidator::~Uint8HexValidator( ) {

}
