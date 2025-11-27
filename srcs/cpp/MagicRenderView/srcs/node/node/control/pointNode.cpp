#include "pointNode.h"
bool PointNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] {
		return nullptr;
	};
	return updateLayout( );
}
bool PointNode::updateLayout( ) {
	return true;
}
