#include "clickBtn.h"

#include <app/application.h>
#include <director/renderImageDirector.h>
#include <QPainter>
ClickBtn::ClickBtn( QWidget *parent ) : QWidget( parent ) {
	image = new QImage( );
}
ClickBtn::~ClickBtn( ) {
	delete image;
}
QImage & ClickBtn::getImage( ) const { return *image; }
void ClickBtn::setImage( QImage &image ) {
	*this->image = image;
}
const QString & ClickBtn::getText( ) const {
	return text;
}
void ClickBtn::setText( const QString &text ) {
	if( Application::getInstancePtr( )->getRenderImageDirector( )->renderText( text, Qt::GlobalColor::red, *image ) == false )
		return;
	this->text = text;
}
void ClickBtn::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.drawImage( 0, 0, *image );
}
