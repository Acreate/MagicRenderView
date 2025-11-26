#include "node.h"
#include <QPainter>
Node::~Node( ) {
	emit release_node_signal( this );
}
Node::Node( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) { }
void Node::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::green );
}
