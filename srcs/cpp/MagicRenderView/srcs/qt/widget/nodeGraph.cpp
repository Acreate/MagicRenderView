#include "nodeGraph.h"
#include <QMouseEvent>

#include <qt/menu/nodeAddMenu.h>

NodeGraph::NodeGraph( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	nodeMenu = new NodeAddMenu( this );
}
NodeGraph::~NodeGraph( ) {
}
void NodeGraph::mouseReleaseEvent( QMouseEvent *event ) {
	nodeMenu->move( QCursor::pos( ) );
	nodeMenu->show( );
}
