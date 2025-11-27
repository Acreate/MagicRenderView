#include "whileNode.h"
bool WhileNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] {
		return nullptr;
	};
	return updateLayout( );
}
bool WhileNode::updateLayout( ) {
	return true;
}
