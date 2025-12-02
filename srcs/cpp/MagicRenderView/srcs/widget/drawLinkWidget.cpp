#include "drawLinkWidget.h"

#include <QPainter>
#include <qevent.h>

#include "../app/application.h"

#include "../director/nodeDirector.h"

DrawLinkWidget::DrawLinkWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
	isDrawLine = false;
}
DrawLinkWidget::~DrawLinkWidget( ) {
	emit release_signal( this );
}
void DrawLinkWidget::drawBegin( const QPoint &start_point ) {
	isDrawLine = true;
	startPoint = start_point;
}
void DrawLinkWidget::drawLinePoint( const QPoint &end_point ) {
	endPoint = end_point;
}
void DrawLinkWidget::drawEnd( ) {
	isDrawLine = false;
}
void DrawLinkWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void DrawLinkWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	if( isDrawLine == true )
		painter.drawLine( startPoint, endPoint );
	nodeDirector->drawLinkLines( painter );
}
