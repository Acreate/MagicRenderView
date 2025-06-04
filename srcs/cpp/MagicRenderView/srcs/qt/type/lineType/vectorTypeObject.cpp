#include "vectorTypeObject.h"
QString VectorTypeObject::toString( ) const {
	QStringList result;
	for( auto elemt : *vector )
		result.append( elemt->toString( ) );
	return "(" + result.join( "," ) + ")";
}
