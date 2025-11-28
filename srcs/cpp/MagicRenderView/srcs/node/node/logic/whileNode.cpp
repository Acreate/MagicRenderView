#include "whileNode.h"
bool WhileNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] ( VarDirector * local_var_director) {
		return nullptr;
	};
	return updateLayout( );
}
bool WhileNode::updateLayout( ) {
	return true;
}
