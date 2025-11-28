#include "beginNode.h"
bool BeginNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] ( VarDirector * local_var_director) {
		return nullptr;
	};
	return updateLayout( );
}
bool BeginNode::updateLayout( ) {
	return true;
}
