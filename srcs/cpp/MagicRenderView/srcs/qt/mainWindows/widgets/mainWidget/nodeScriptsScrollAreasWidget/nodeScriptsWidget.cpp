#include "./nodeScriptsWidget.h"

#include <QPainter>

#include <qt/application/application.h>
NodeScriptsWidget::NodeScriptsWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	applicationInstancePtr = Application::getApplicationInstancePtr( );
	connect( applicationInstancePtr, &Application::dragEventEnd, this, &NodeScriptsWidget::dragEventEnd );
}
NodeScriptsWidget::~NodeScriptsWidget( ) {
}
void NodeScriptsWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	auto rect = contentsRect( );
	painter.fillRect( rect, Qt::red );
	QPen pen( Qt::GlobalColor::black );
	int width = 4;
	pen.setWidth( width );
	painter.setPen( pen );
	painter.setBrush( QColor( 0, 0, 0, 0 ) );
	auto size = rect.size( );
	painter.drawRect( width, width, size.width( ) - width * 2 - 1, size.height( ) - width * 2 - 1 );
}
void NodeScriptsWidget::dragEventEnd( Application *event_obj, QWidget *draw_widget ) {
	auto point = QCursor::pos( );
	auto fromGlobal = mapFromGlobal( point );
	if( contentsRect( ).contains( fromGlobal ) == false )
		return;
	qDebug( ) << "处理范围";
}
