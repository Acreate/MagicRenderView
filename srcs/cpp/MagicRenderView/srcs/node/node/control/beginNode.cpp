#include "beginNode.h"
bool BeginNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] {
		return nullptr;
	};
	return updateLayout( );
}
bool BeginNode::updateLayout( ) {
	return true;
}
