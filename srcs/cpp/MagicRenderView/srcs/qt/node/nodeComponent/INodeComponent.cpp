#include "INodeComponent.h"

#include <QPainter>
void INodeComponent::setNewSize( const QSize &new_size ) {
	setFixedSize( new_size );
	emit changeSize( new_size );
}
void INodeComponent::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	/*QPainter painter( this );
	QPen pen;
	QBrush brush;
	pen.setWidth( 5 );
	pen.setColor( Qt::red );
	painter.setPen( pen );
	auto geometry = size( );
	painter.drawRect( QRect( 0, 0, geometry.width( ) - 1, geometry.height( ) - 1 ) );*/
}
