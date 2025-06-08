#include "./INodeWidget.h"

#include "qt/widget/nodeGraph.h"
#include <QMouseEvent>
void INodeWidget::connectNodeGraphWidget( NodeGraph *node_graph ) {
	connect( this, &INodeWidget::selectNodeComponent, node_graph, &NodeGraph::selectNodeComponent );
	connect( this, &INodeWidget::error, node_graph, &NodeGraph::error );
	connect( this, &INodeWidget::finish, node_graph, &NodeGraph::finish );
}
void INodeWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	QWidget *component = childAt( event->pos( ) );
	emit selectNodeComponent( this, component );
}
