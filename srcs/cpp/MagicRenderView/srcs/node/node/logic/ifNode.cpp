#include "ifNode.h"
bool IfNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] {
		return nullptr;
	};
	return updateLayout( );
}
bool IfNode::updateLayout( ) {
	return true;
}
