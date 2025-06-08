#include "INodeWidget.h"

#include "qt/widget/nodeGraph.h"
#include <QMouseEvent>
#include <QPainter>
void INodeWidget::connectNodeGraphWidget( NodeGraph *node_graph ) {
	connect( this, &INodeWidget::selectNodeComponentRelease, node_graph, &NodeGraph::selectNodeComponentRelease );
	connect( this, &INodeWidget::selectNodeComponentPress, node_graph, &NodeGraph::selectNodeComponentPress );
	connect( this, &INodeWidget::error, node_graph, &NodeGraph::error );
	connect( this, &INodeWidget::finish, node_graph, &NodeGraph::finish );
}
void INodeWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	QPoint pos = event->pos( );
	QWidget *component = childAt( pos );
	emit selectNodeComponentRelease( this, component, pos );
}
void INodeWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	QPoint pos = event->pos( );
	QWidget *component = childAt( pos );
	emit selectNodeComponentPress( this, component, pos );
}
void INodeWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	QPen pen;
	QBrush brush;
	pen.setWidth( 5 );
	pen.setColor( Qt::red );
	painter.setPen( pen );
	auto geometry = size( );
	painter.drawRect( QRect( 0, 0, geometry.width( ) - 1, geometry.height( ) - 1 ) );
}
