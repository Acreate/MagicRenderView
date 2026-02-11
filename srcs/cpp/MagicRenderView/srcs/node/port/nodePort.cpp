#include "nodePort.h"

#include <node/node/node.h>
NodePort::NodePort( ) {
	parentNode = nullptr;
	varDirectorPtr = nullptr;
	varPtr = nullptr;
}
VarDirector * NodePort::getVarDirector( ) const {
	if( varDirectorPtr )
		return varDirectorPtr;
	if( parentNode )
		return parentNode->getVarDirector( );
	return nullptr;
}
