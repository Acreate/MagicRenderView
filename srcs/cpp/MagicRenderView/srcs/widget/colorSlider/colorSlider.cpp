#include "colorSlider.h"

#include <qcoreevent.h>
#include <QResizeEvent>
#include <widget/clickBtn/clickBtn.h>

#define Reinterpret_Cast( source_ptr, cast_ptr ) source_ptr = reinterpret_cast< decltype(source_ptr) >( cast_ptr )

void ColorSlider::resizeWidget( const QSize &old_size, const QSize &new_size ) {
	int height = new_size.height( );
	clickBtn->resize( height, height );
}
void ColorSlider::rePainterWidget( ) {
}
ColorSlider::ColorSlider( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	clickBtn = new ClickBtn( this );
	int height = this->height( );
	clickBtn->resize( height, height );
	clickBtn->move( 0, 0 );
	clickBtn->setText( tr( "透明度" ) );
}

bool ColorSlider::eventFilter( QObject *watched, QEvent *event ) {
	return QWidget::eventFilter( watched, event );
}
bool ColorSlider::event( QEvent *event ) {
	auto type = event->type( );
	QResizeEvent *resizeEvent;
	QMouseEvent *mouseEvent;
	switch( type ) {
		case QEvent::Paint :
			return true;
		case QEvent::Resize :
			Reinterpret_Cast( resizeEvent, event );
			if( resizeEvent == nullptr )
				break;
			resizeWidget( resizeEvent->oldSize( ), resizeEvent->size( ) );
			return true;
		case QEvent::MouseButtonPress :
			Reinterpret_Cast( mouseEvent, event );
			if( mouseEvent == nullptr )
				break;
			if( mouseEvent->button( ) == Qt::MouseButton::LeftButton ) {
				return true;
			}
			break;
	}
	return QWidget::event( event );
}
