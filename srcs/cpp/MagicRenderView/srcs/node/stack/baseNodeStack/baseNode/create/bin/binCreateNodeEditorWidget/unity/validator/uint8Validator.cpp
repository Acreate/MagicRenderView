#include "uint8Validator.h"

Uint8Validator::~Uint8Validator( ) {

}
QValidator::State Uint8Validator::validate( QString &in_put, int &in_pos ) const {
	if( in_put.isEmpty( ) )
		return Acceptable;
	if( in_put.length( ) > 3 )
		return Invalid;
	bool isOK;
	ulong uLong = in_put.toULong( &isOK );
	if( isOK == false || uLong > 255 )
		return Invalid;
	return Acceptable;
}
