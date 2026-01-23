#include "charHexValidator.h"
CharHexValidator::CharHexValidator( QObject *parent ) : SignedValidator( UINT16_MAX, 0, 16, parent ) {
}
CharHexValidator::~CharHexValidator( ) {

}
