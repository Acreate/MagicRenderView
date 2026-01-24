#include "uInt8HexValidator.h"

UInt8HexValidator::UInt8HexValidator( QObject *parent ) : UnSignedValidator( UINT8_MAX, 0, 16, parent ) {
}
UInt8HexValidator::~UInt8HexValidator( ) {

}
