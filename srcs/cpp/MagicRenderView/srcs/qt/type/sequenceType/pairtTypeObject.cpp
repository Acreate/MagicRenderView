#include "pairtTypeObject.h"
PairtTypeObject::PairtTypeObject( QObject *parent ): ITypeObject( parent ) {
}
QString PairtTypeObject::toString( ) const {
	QString resultString( "(" );
	if( first )
		resultString = resultString + first->toString( );
	if( scond )
		resultString = resultString + "," + first->toString( ) + ")";
	return resultString;
}
