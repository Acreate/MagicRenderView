#include "jumpNode.h"
bool JumpNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] {
		return nullptr;
	};
	return updateLayout( );
}
bool JumpNode::updateLayout( ) {
	return true;
}
