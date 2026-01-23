#include "int64DecValidator.h"

Int64DecValidator::Int64DecValidator( QObject *parent ) : SignedValidator( INT64_MAX, INT64_MIN, 10, parent ) {
}
Int64DecValidator::~Int64DecValidator( ) {

}