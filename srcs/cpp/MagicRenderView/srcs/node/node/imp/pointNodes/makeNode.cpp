#include "makeNode.h"
MakeNode::MakeNode( QWidget *parent, const Qt::WindowFlags &f ): PointNode( parent, f ) { }
bool MakeNode::updateLayout( ) {
	return true;
}
