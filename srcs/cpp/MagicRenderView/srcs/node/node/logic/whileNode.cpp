#include "whileNode.h"
bool WhileNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] {
	};
	return updateLayout( );
}
bool WhileNode::updateLayout( ) {
	return true;
}
