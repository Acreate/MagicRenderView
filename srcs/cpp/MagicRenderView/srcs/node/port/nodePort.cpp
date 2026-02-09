
#include "nodePort.h"

#include <node/node/node.h>
VarDirector * NodePort::getVarDirector( ) const {
	if( varDirectorPtr )
		return varDirectorPtr;
	if( parentNode )
		return parentNode->getVarDirector( );
	return nullptr;
}
