#include "uInt32HexValidator.h"
UInt32HexValidator::UInt32HexValidator( QObject *parent ) : UnSignedValidator( UINT32_MAX, 0, 16, parent ) {
}
UInt32HexValidator::~UInt32HexValidator( ) {

}
