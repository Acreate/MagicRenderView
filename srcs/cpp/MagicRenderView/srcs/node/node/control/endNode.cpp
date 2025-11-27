#include "endNode.h"
bool EndNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] {
		return nullptr;
	};
	return updateLayout( );
}
bool EndNode::updateLayout( ) {
	return true;
}
