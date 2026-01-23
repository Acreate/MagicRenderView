#include "uInt64HexValidator.h"

UInt64HexValidator::UInt64HexValidator( QObject *parent ) : UnSignedValidator( UINT64_MAX, 0, 16, parent ) {
}
UInt64HexValidator::~UInt64HexValidator( ) {

}
