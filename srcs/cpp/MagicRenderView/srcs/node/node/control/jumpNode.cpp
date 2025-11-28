#include "jumpNode.h"
bool JumpNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] ( VarDirector * local_var_director) {
		return nullptr;
	};
	return updateLayout( );
}
bool JumpNode::updateLayout( ) {
	return true;
}
