#include "endNode.h"
bool EndNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] ( VarDirector * local_var_director) {
		return nullptr;
	};
	return updateLayout( );
}
bool EndNode::updateLayout( ) {
	return true;
}
