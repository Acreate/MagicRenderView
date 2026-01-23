#include "charDecValidator.h"
CharDecValidator::CharDecValidator( QObject *parent ) : SignedValidator( UINT16_MAX, 0, 10, parent ) {
}
CharDecValidator::~CharDecValidator( ) {

}
