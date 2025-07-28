#include "./nodeListWidget.h"

#include <QPainter>
#include <QListWidget>
#include <qboxlayout.h>

#include "gridWidget.h"
NodeListWidget::NodeListWidget( QWidget *parent, Qt::WindowFlags flags ): QWidget( parent, flags ) {
	mainLayout = new QHBoxLayout( this );
	mainLayout->setSpacing( 0 );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	nodeTypeList = new QListWidget( this );
	nodeGeneraterList = new GridWidget( this );
	mainLayout->addWidget( nodeTypeList, 2 );
	mainLayout->addWidget( nodeGeneraterList, 8 );
}
NodeListWidget::~NodeListWidget( ) {
}
void NodeListWidget::paintEvent( QPaintEvent *event ) {

	QWidget::paintEvent( event );
	QPainter painter( this );
	auto rect = contentsRect( );
	painter.fillRect( rect, Qt::blue );
	QPen pen( Qt::GlobalColor::black );
	int width = 4;
	pen.setWidth( width );
	painter.setPen( pen );
	painter.setBrush( QColor( 0, 0, 0, 0 ) );
	auto size = rect.size( );
	painter.drawRect( width, width, size.width( ) - width * 2 - 1, size.height( ) - width * 2 - 1 );
}
