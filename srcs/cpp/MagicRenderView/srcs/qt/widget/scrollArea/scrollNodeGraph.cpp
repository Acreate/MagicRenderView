#include "scrollNodeGraph.h"

#include <qt/widget/nodeGraph.h>
ScrollNodeGraph::ScrollNodeGraph( QWidget *parent ): QScrollArea( parent ) {
	nodeGraph = new NodeGraph( this );
	setWidget( nodeGraph );
	setWidgetResizable( true );
}
ScrollNodeGraph::~ScrollNodeGraph( ) {
}