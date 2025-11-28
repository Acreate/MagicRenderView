#include "pointNode.h"
bool PointNode::init( QWidget *parent ) {
	if( Node::init( parent ) == false )
		return false;
	nodeFunction = [] ( VarDirector * local_var_director) {
		return nullptr;
	};
	return updateLayout( );
}
bool PointNode::updateLayout( ) {
	return true;
}
