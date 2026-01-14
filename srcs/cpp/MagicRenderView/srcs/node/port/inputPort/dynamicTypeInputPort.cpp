#include "dynamicTypeInputPort.h"
bool DynamicTypeInputPort::init( Node *parent ) {
	if( InputPort::init( parent ) == false )
		return false;
	return true;
}
