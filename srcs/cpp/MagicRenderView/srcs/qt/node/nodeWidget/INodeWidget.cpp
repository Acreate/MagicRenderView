#include "./INodeWidget.h"

#include "qt/widget/nodeGraph.h"
void INodeWidget::connectNodeGraphWidget( NodeGraph *node_graph ) {
	connect( this, &INodeWidget::selectNodeWidgetBody, node_graph, &NodeGraph::selectNodeWidgetBody );
}
