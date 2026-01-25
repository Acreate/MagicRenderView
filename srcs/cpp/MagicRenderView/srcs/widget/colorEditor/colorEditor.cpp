#include "colorEditor.h"

#include <define/castMacro.h>
#include <qcoreevent.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <qpushbutton.h>
void ColorEditor::affirmBtenClick( ) {

}
void ColorEditor::cancelBtenClick( ) {
}
ColorEditor::ColorEditor( QWidget *parent ) : QWidget( parent ) {
	alphaScrollButton = new QLabel( tr( "透" ), this );
	affirmBtn = new QLabel( tr( "确定" ), this );
	cancelBen = new QLabel( tr( "取消" ), this );
	selectPoint = new QLabel( this );
	QImage image( ":/imageIco/color_picking.png" );
	QPixmap fromImage = QPixmap::fromImage( image );
	selectPoint->setPixmap( fromImage );
	selectPointBackground = new QImage( );
	alphaScrollBackground = new QImage( );
}
ColorEditor::~ColorEditor( ) {
	delete selectPointBackground;
	delete alphaScrollBackground;
}

void ColorEditor::setCurrentColor( const QColor &current_color ) {
	currentColor = current_color;
	repaint( ); // 属性面板
}
bool ColorEditor::eventFilter( QObject *watched, QEvent *event ) {
	auto type = event->type( );
	QPainter *painter;
	QMouseEvent *mouseEventPtr;
	int drawXPos;
	int height;
	int width;
	double value;
	switch( type ) {
		case QEvent::MouseButtonRelease :
			Reinterpret_Cast( mouseEventPtr, event );
			if( watched == affirmBtn ) {
				emit selectorColor( currentColor );
				hide( );
				return true;
			} else if( watched == cancelBen ) {
				hide( );
				return true;
			} else if( watched == alphaScrollButton )
				return true; // 滑动窗口
			return true; // 已经处理的即返回
		case QEvent::Paint :
			if( alphaScrollButton != watched ) {
				// 高度
				height = alphaScrollButton->height( );
				// 宽度
				width = alphaScrollButton->width( );
				// 角度
				value = 45;
				// 因子
				value = value * ( M_PI / 180.0 );
				// tan 值
				value = std::tan( value );
				// 相差像素
				value = height / value;
				// 间隔
				nextInterval = 4;
				painter = new QPainter( alphaScrollButton );
				painter->setPen( Qt::GlobalColor::red );
				drawXPos = 0;
				width += width; // 增加底部宽度
				while( true ) {
					painter->drawLine( drawXPos, 0, drawXPos - value, height );
					if( drawXPos > width )
						break;
					drawXPos += nextInterval;
				}
				delete painter;
				return true;
			}
			break;
	}
	return QWidget::eventFilter( watched, event );
}
bool ColorEditor::event( QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::Show :
			return true;
		case QEvent::Hide :
			return true;
		case QEvent::Paint :
			return true;
		case QEvent::Resize :
			return true;
	}
	return QWidget::event( event );
}
