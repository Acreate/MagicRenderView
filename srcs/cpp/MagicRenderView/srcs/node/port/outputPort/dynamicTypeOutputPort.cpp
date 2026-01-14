#include "dynamicTypeOutputPort.h"
bool DynamicTypeOutputPort::init( Node *parent ) {
	if( OutputPort::init( parent ) == false )
		return false;
	return true;
}
